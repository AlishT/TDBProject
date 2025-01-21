// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "BoxProject/Projectile/Projectile.h"
#include "BoxProject/Pawn/BasePawn.h"
#include "BoxProject/ProjectileType.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<ABasePawn>(GetOwner());

	SetDefaultProjectile();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CurrentFireTime += DeltaTime;
}

void UCombatComponent::Shoot()
{
	FireTimer();
}

void UCombatComponent::FireTimer()
{
	if (CurrentFireTime >= FireRate)
	{
		FireTimerFinished();
		CurrentFireTime = 0.f;
	}
}

void UCombatComponent::FireTimerFinished()
{
	SetSpawnWeapons(ProjectileType);
}

void UCombatComponent::NewProjectileTimer(float DeltaTime)
{
	if (ProjectileType != EProjectileType::EPT_DefaultBullet)
	{
		CurrentTime += DeltaTime;

		if (CurrentTime >= ProjectileTime)
		{
			SetDefaultProjectile();
		}
	}
}

void UCombatComponent::SetSpawnWeapons(EProjectileType Type)
{
	switch (Type)
	{
	case EProjectileType::EPT_DefaultBullet:
	case EProjectileType::EPT_SingleRocket:
	case EProjectileType::EPT_ArmoredBullet:
	case EProjectileType::EPT_Lazer:
		UseFrontWeapon();
		break;
	case EProjectileType::EPT_TwoRockets:
	case EProjectileType::EPT_TwoDefaultBullet:
	case EProjectileType::EPT_TwoArmoredBullet:
	case EProjectileType::EPT_TwoLazer:
		UseLeftRightWeapons();
		break;
	case EProjectileType::EPT_ThreeDefaultBullets:
	case EProjectileType::EPT_ThreeArmoredBullets:
	case EProjectileType::EPT_ThreeRockets:
	case EProjectileType::EPT_ThreeLazer:
		UseAllWeapons();
		break;
	}
}

void UCombatComponent::SpanwWeaponsProjectile(float WeaponId)
{
	if (!Pawn) return;

	FVector Location = Weapons[WeaponId]->GetComponentLocation();
	FRotator Rotation = Weapons[WeaponId]->GetComponentRotation();

	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Weapons[WeaponId], FName(), Location, Rotation, EAttachLocation::KeepWorldPosition);
	}

	if (ShootSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, Location);
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Pawn;
	SpawnParams.Instigator = Pawn->GetInstigator();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation, SpawnParams);

	if (Projectile)
	{
		Projectile->FireInDirection(Rotation.Vector());
	}
}

void UCombatComponent::SetProjectileType(const EProjectileType Type)
{
	ProjectileType = Type;
	CurrentTime = 0.f;
}

void UCombatComponent::UseFrontWeapon()
{
	if (Pawn)
	{
		Weapons = Pawn->GetWeapons();
	}

	SpanwWeaponsProjectile(0);
}

void UCombatComponent::UseLeftRightWeapons()
{
	if (Pawn)
	{
		Weapons = Pawn->GetWeapons();
	}

	for (int i = 1; i < Weapons.Num(); i++)
	{
		SpanwWeaponsProjectile(i);
	}
}

void UCombatComponent::UseAllWeapons()
{
	if (Pawn)
	{
		Weapons = Pawn->GetWeapons();
	}

	for (int i = 0; i < Weapons.Num(); i++)
	{
		SpanwWeaponsProjectile(i);
	}
}

void UCombatComponent::SetDefaultProjectile()
{
	if (DefaultProjectileClass)
	{
		ProjectileClass = DefaultProjectileClass;
		ProjectileType = ProjectileTypeDefault;
		SetWeaponsParams(ProjectileType);
		CurrentFireTime = FireRate;
	}
}

FWeaponsData* UCombatComponent::SetDataRow(const FName& Name)
{
	/*const FString WeaponTablePath{TEXT("/Script/Engine.DataTable'/Game/Blueprints/WeaponsDataTable.WeaponsDataTable'")};
	UDataTable* WeaponsTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *WeaponTablePath));

	if (WeaponsTableObject)
	{
		return WeaponsTableObject->FindRow<FWeaponsData>(FName(Name), TEXT(""));
	}*/

	if (WeaponDataTable)
	{
		return WeaponDataTable->FindRow<FWeaponsData>(FName(Name), "");
	}

	return nullptr;
}

void UCombatComponent::SetWeaponsParams(EProjectileType Type)
{
	FName DataRowName = GetDataRowName(Type);

	FWeaponsData* WeaponsDataRow = SetDataRow(DataRowName);

	if (WeaponsDataRow)
	{
		MuzzleFlash = WeaponsDataRow->MuzzleFlash;
		ShootSound= WeaponsDataRow->ShootSound;
		FireRate = WeaponsDataRow->FireRate;

		CurrentFireTime = FireRate;
	}

}

FName UCombatComponent::GetDataRowName(EProjectileType Type)
{
	FName DataRowName = "None";

	switch (Type)
	{
	case EProjectileType::EPT_DefaultBullet:
	case EProjectileType::EPT_TwoDefaultBullet:
	case EProjectileType::EPT_ThreeDefaultBullets:
		DataRowName = "Default";
		break;
	case EProjectileType::EPT_ArmoredBullet:
	case EProjectileType::EPT_TwoArmoredBullet:
	case EProjectileType::EPT_ThreeArmoredBullets:
		DataRowName = "Armored";
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
