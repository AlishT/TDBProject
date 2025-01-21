// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "BoxProject/Components/CombatComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BoxProject/Components/HealthComponent.h"
#include "BoxProject/Components/AbilityComponent.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"
#include "BoxProject/Controllers/BasePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "BoxProject/Interfaces/CrosshairInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "BoxProject/Pawn/EnemyPawn.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"

APlayerPawn::APlayerPawn()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom);

	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentCrosshairTime += DeltaTime;

	if (CurrentCrosshairTime >= CrosshairOffTime)
	{
		ShowCrosshair();
		CurrentCrosshairTime = 0.f;
	}

	if (GetCombat())
	{
		GetCombat()->NewProjectileTimer(DeltaTime);
	}
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* PlayerEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerEnhancedInput)
	{
		PlayerEnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
		//PlayerEnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APlayerPawn::MoveRight);
		PlayerEnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerPawn::Look);
		PlayerEnhancedInput->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerPawn::Fire);
		PlayerEnhancedInput->BindAction(PauseMenuAction, ETriggerEvent::Triggered, this, &APlayerPawn::OpenPauseMenu);
	}
}

void APlayerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D Direction = Value.Get<FVector2D>();
	//float Direction = Value.Get<float>();
	
	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		/*float ForwardValue = MovementVector.X;
		float RightValue  = MovementVector.Y;
		FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetSafeNormal();
		FVector MoveVelocity = MoveDirection * 10 ;
		AddActorWorldOffset(MoveVelocity, true);*/
		
		AddMovementInput(ForwardDirection, Direction.Y, false);
		AddMovementInput(RightDirection, Direction.X, false);

		//FVector Location = GetActorForwardVector() * Speed * Direction;
		//FVector Location = FVector(Direction, 0.f, 0.f).GetSafeNormal() * Speed;
		//AddActorLocalOffset(Location);
		//AddActorLocalRotation(Location.Rotation());
	}
}

void APlayerPawn::Look(const FInputActionValue& Value)
{
	/*FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

	}*/
	
	const float RotationValue = Value.Get<float>();

	if (!Controller && RotationValue == 0)
	{
		return;
	}

	FRotator Rotation = FRotator(0.f, RotationValue * RotationSpeed, 0.f);

	AddActorLocalRotation(Rotation, true, 0, ETeleportType::ResetPhysics);
}

void APlayerPawn::Fire()
{
	if (!GetCombat()) return;

	if (WallCheced())
	{
		GetCombat()->Shoot();
		MakeNoise();
	}
}

void APlayerPawn::OpenPauseMenu()
{
	ABasePlayerController* PlayerController = GetController<ABasePlayerController>();
	
	if (!PlayerController) return;

	PlayerController->OpenPauseMenu();
}

void APlayerPawn::ShowCrosshair()
{
	FHitResult Hit;
	FVector StartPoaint = GetFrontWeaponMuzzle()->GetComponentLocation();
	FVector EndPoint = StartPoaint + GetFrontWeaponMuzzle()->GetForwardVector() * AimDistance;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, StartPoaint, EndPoint, ECollisionChannel::ECC_Visibility, QueryParams);

	//DrawDebugLine(GetWorld(), StartPoaint, EndPoint, Hit.bBlockingHit ? FColor::Red : FColor::Green, false, 0.1f, 0, 5.0f);

	ICrosshairInterface* CrosshairInterface = Cast<ICrosshairInterface>(Hit.GetActor());

	if (IsValid(Hit.GetActor()) && Hit.GetActor()->IsA(AEnemyPawn::StaticClass()))
	{
		if (TargetSystem)
		{
			UGameplayStatics::SpawnEmitterAttached(TargetSystem, Hit.GetActor()->GetRootComponent(), FName(), Hit.GetActor()->GetActorLocation(), Hit.GetActor()->GetActorRotation(), EAttachLocation::KeepWorldPosition);
		}
	}
}

bool APlayerPawn::WallCheced()
{
	FHitResult Hit;
	FVector StartPoaint = GetActorLocation();
	FVector EndPoint = StartPoaint + GetActorForwardVector() * 60.f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, StartPoaint, EndPoint, ECollisionChannel::ECC_Visibility, QueryParams);

	//DrawDebugLine(GetWorld(), StartPoaint, EndPoint, Hit.bBlockingHit ? FColor::Red : FColor::Green, false, 0.1f, 0, 5.0f);

	ICrosshairInterface* CrosshairInterface = Cast<ICrosshairInterface>(Hit.GetActor());

	return (Hit.bBlockingHit) ? false : true;
}


void APlayerPawn::IncreasePlayerStats(float Percent, UBoxGameInstance* GameInstance)
{
	if (!GameInstance) return;

	if (GetCombat())
	{
		float NewProjetileTime = IncreaseProperty(GetCombat()->GetProjectileTime(), Percent);
		GetCombat()->SetProjectileTime(NewProjetileTime); 
		GameInstance->SetProcjetileTime(NewProjetileTime);
	}

	if (GetHealthComponent())
	{
		float NewMaxHealth = IncreaseProperty(GetHealthComponent()->GetMaxHealth(), Percent);
		GetHealthComponent()->SetMaxHealth(NewMaxHealth);
		GetHealthComponent()->UpdateCurrentHealth();
		GameInstance->SetMaxHealth(NewMaxHealth);
	}

	if (GetAbilityComponent())
	{
		float NewShieldTime = IncreaseProperty(GetAbilityComponent()->GetShieldTime(), Percent);
		GetAbilityComponent()->SetShieldTime(NewShieldTime);
		GameInstance->SetShieldTime(NewShieldTime);

		float NewEnergyTime = IncreaseProperty(GetAbilityComponent()->GetEnergyTime(), Percent);
		GetAbilityComponent()->SetEnergyTime(NewEnergyTime);
		GameInstance->SetEnergyTime(NewEnergyTime);
	}
}

void APlayerPawn::UpdatePlayerStats(UBoxGameInstance* GameInstance)
{
	if (!GameInstance) return;

	if (GetCombat())
	{
		float Time = GameInstance->GetProjectileTime();
		GetCombat()->SetProjectileTime(Time);
	}

	if (GetHealthComponent())
	{
		float Health = GameInstance->GetMaxHealth();
		GetHealthComponent()->SetMaxHealth(Health);
	}

	if (GetAbilityComponent())
	{
		float ShieldTime = GameInstance->GetShieldTime();
		GetAbilityComponent()->SetShieldTime(ShieldTime);

		float EnergyTime = GameInstance->GetEnergyTime();
		GetAbilityComponent()->SetEnergyTime(EnergyTime);
	}
}

void APlayerPawn::ShowLevelUpSystem()
{
	if (LevelUpSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(LevelUpSystem, GetRootComponent(), FName(), GetActorLocation(), GetActorRotation(), EAttachLocation::KeepWorldPosition, false);
	}

	if (LevelUpSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), LevelUpSound);
	}
}

float APlayerPawn::IncreaseProperty(float Prop, float Percent)
{
	return Prop + Prop * Percent / 100;
}

/*void APlayerPawn::MoveRight(const FInputActionValue& Value)
{
	float Direction = Value.Get<float>();
	
	if (Controller)
	{
		//FVector Location = GetActorRightVector() * Speed * Direction;
		FVector Location = FVector(0.f, Direction, 0.f).GetSafeNormal() * Speed;
		AddActorLocalOffset(Location);
		//AddActorLocalRotation(Location.Rotation());
	}
}*/
