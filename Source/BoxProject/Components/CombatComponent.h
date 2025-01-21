// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoxProject/ProjectileType.h"
#include "CombatComponent.generated.h"

class AProjectile;
class ABasePawn;
class UParticleSystem;
class USoundCue;

USTRUCT(BlueprintType)
struct BOXPROJECT_API FWeaponsData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName Name = "None";

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleFlash = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	USoundCue* ShootSound = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float FireRate = 0.f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOXPROJECT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Transient)
	ABasePawn* Pawn = nullptr;

	UPROPERTY()
	TArray<USceneComponent*> Weapons;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> DefaultProjectileClass;

	UPROPERTY(Transient)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	EProjectileType ProjectileTypeDefault = EProjectileType::EPT_DefaultBullet;

	UPROPERTY(Transient)
	EProjectileType ProjectileType = EProjectileType::EPT_DefaultBullet;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileTime = 0.f;

	UPROPERTY()
	float CurrentTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	class UDataTable* WeaponDataTable = nullptr;

	UPROPERTY()
	UParticleSystem* MuzzleFlash = nullptr;

	UPROPERTY()
	USoundCue* ShootSound = nullptr;

	UPROPERTY()
	float FireRate = 0.f;

	UPROPERTY()
	float CurrentFireTime = 0.f;

	UPROPERTY()
	bool bCanFire = false;

	UPROPERTY()
	FTimerHandle TimeHandle;

	void SetSpawnWeapons(EProjectileType Type);

	void UseFrontWeapon();

	void UseLeftRightWeapons();

	void UseAllWeapons();

	void SetDefaultProjectile();

	FWeaponsData* SetDataRow(const FName& Name);

	FName GetDataRowName(EProjectileType Type);

	void FireTimer();

	void FireTimerFinished();
	
public:
	UFUNCTION(BlueprintCallable)
	void Shoot();

	void NewProjectileTimer(float DeltaTime);

	void SetWeaponsParams(EProjectileType Type);

	void SpanwWeaponsProjectile(float WeaponId);

	void SetProjectileType(const EProjectileType Type);

	FORCEINLINE void SetProjectileClass(const TSubclassOf<AActor> ActorClass) { ProjectileClass = ActorClass; }
	FORCEINLINE float GetProjectileTime() const { return ProjectileTime; }
	FORCEINLINE void SetProjectileTime(const float Time) { ProjectileTime = Time; }
};
