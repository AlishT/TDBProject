// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(CollisionBox);
	ProjectileMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_OverlapAll_Deprecated, ECollisionResponse::ECR_Ignore);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionBox->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->SetUpdatedComponent(CollisionBox);
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.1f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 2.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (TracerPartical)
	{
		UGameplayStatics::SpawnEmitterAttached(TracerPartical, CollisionBox,FName(), GetActorLocation(), GetActorRotation(), EAttachLocation::KeepWorldPosition);
	}

	if (TrailSystem)
	{
		TrailSystemComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TrailSystem, GetRootComponent(), FName(), GetActorLocation(), GetActorRotation(), EAttachLocation::KeepWorldPosition, false);
	}
	
}

void AProjectile::OnConstruction(const FTransform& Transform)
{
	SetProjectileParams();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bHit) return;

	if (ProjectileType == EProjectileType::EPT_SingleRocket || ProjectileType == EProjectileType::EPT_TwoRockets || ProjectileType == EProjectileType::EPT_ThreeRockets)
	{
		CurrentTime += DeltaTime;
		
		if (CurrentTime >= DestroyTime)
		{
			Destroy();
		}
	}
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ImpactPartical)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactPartical, GetActorTransform());
	}

	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
	}

	if (GetOwner())
	{
		AController* OwnerInstigator = GetOwner()->GetInstigatorController();
		UClass* DamageTypeClass = UDamageType::StaticClass();

		UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, DamageTypeClass);
	}

	if (ProjectileType != EProjectileType::EPT_TwoRockets && ProjectileType != EProjectileType::EPT_SingleRocket && ProjectileType != EProjectileType::EPT_ThreeRockets)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Destroy"));
		Destroy();
	}

	bHit = true;

	if (ProjectileMesh)
	{
		ProjectileMesh->SetVisibility(false);
	}

	if (CollisionBox)
	{
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (TrailSystemComponent)
	{
		TrailSystemComponent->Deactivate();
	}
}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}

void AProjectile::SetProjectileParams()
{
	FName DataRow = GetDataRowName(ProjectileType);

	FProjectileData* ProjectileDataRow = SetDataRow(DataRow);

	if (ProjectileDataRow)
	{
		Damage = ProjectileDataRow->Damage;
		ProjectileMovement->InitialSpeed = ProjectileDataRow->ProjectileSpeed;
		ProjectileMovement->MaxSpeed = ProjectileDataRow->ProjectileSpeed;
		ProjectileMesh->SetStaticMesh(ProjectileDataRow->ProjectileMesh);
		TrailSystem = ProjectileDataRow->TrailSystem;
		TracerPartical = ProjectileDataRow->TracerPartical;
		ImpactPartical = ProjectileDataRow->ImpactPartical;
		ImpactSound = ProjectileDataRow->ImpactSound;
	}
}

FProjectileData* AProjectile::SetDataRow(const FName& Name)
{
	/*const FString ProjectileTablePath{TEXT("/Script/Engine.DataTable'/Game/Blueprints/ProjectileDataTable.ProjectileDataTable'")};
	UDataTable* ProjectileTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ProjectileTablePath));

	if (ProjectileTableObject)
	{
		return ProjectileTableObject->FindRow<FProjectileData>(FName(Name), TEXT(""));
	}*/
	
	if (ProjectileDataTable)
	{
		return ProjectileDataTable->FindRow<FProjectileData>(FName(Name), "");
	}

	return nullptr;
}

FName AProjectile::GetDataRowName(EProjectileType Type)
{
	FName DataRowName = "None";

	switch (Type)
	{
	case EProjectileType::EPT_DefaultBullet:
	case EProjectileType::EPT_TwoDefaultBullet:
	case EProjectileType::EPT_ThreeDefaultBullets:
		DataRowName = "DefaultBullet";
		break;
	case EProjectileType::EPT_ArmoredBullet:
	case EProjectileType::EPT_TwoArmoredBullet:
	case EProjectileType::EPT_ThreeArmoredBullets:
		DataRowName = "ArmoredBullet";
		break;
	case EProjectileType::EPT_SingleRocket:
		DataRowName = "SingleRocket";
		break;
	case EProjectileType::EPT_TwoRockets:
		DataRowName = "TwoRockets";
		break;
	case EProjectileType::EPT_ThreeRockets:
		DataRowName = "ThreeRockets";
		break;
	case EProjectileType::EPT_Lazer:
	case EProjectileType::EPT_TwoLazer:
	case EProjectileType::EPT_ThreeLazer:
		DataRowName = "Lazer";
		break;
	}

	return DataRowName;
}

