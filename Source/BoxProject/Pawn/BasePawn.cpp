// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BoxProject/Components/CombatComponent.h"
#include "BoxProject/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "BoxProject/GameMode/BaseGameMode.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChenged.AddDynamic(this, &ABasePawn::EliminationHandler);

	FrontWeaponMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("FrontWeaponMuzzle"));
	FrontWeaponMuzzle->SetupAttachment(BaseMesh);
	RightWeaponMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("RightWeaponMuzzle"));
	RightWeaponMuzzle->SetupAttachment(BaseMesh);
	LeftWeaponMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("LeftWeaponMuzzle"));
	LeftWeaponMuzzle->SetupAttachment(BaseMesh);
	
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
	Weapons.Emplace(FrontWeaponMuzzle);
	Weapons.Emplace(RightWeaponMuzzle);
	Weapons.Emplace(LeftWeaponMuzzle);
}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::EliminationHandler(float Health)
{
	if (Health > 0) return;

	if(bElimPawn) return;

	bElimPawn = true;
	
	if (ElimSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ElimSound, GetActorLocation());
	}

	if (ElimEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElimEffect, GetActorLocation());
	}

	ABaseGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();
	
	if (BaseGameMode)
	{
		BaseGameMode->PawnElimHandler(this);
	}
}

