// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxProject/ProjectileType.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class USoundCue;
class UNiagaraSystem;
class UNiagaraComponent;

USTRUCT(BlueprintType)
struct BOXPROJECT_API FProjectileData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName Name = "NONE";

	UPROPERTY(EditDefaultsOnly)
	float Damage = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* TrailSystem = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ImpactPartical = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* TracerPartical = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* ProjectileMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundCue* ImpactSound = nullptr;
};

UCLASS()
class BOXPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "CollisionBox")
	UBoxComponent* CollisionBox = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectileMovementComponent")
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(Transient)
	float Damage = 0.f;

	UPROPERTY(Transient)
	UNiagaraSystem* TrailSystem = nullptr;

	UPROPERTY(Transient)
	UNiagaraComponent* TrailSystemComponent = nullptr;

	UPROPERTY(Transient)
	UParticleSystem* ImpactPartical = nullptr;

	UPROPERTY(Transient)
	UParticleSystem* TracerPartical = nullptr;

	UPROPERTY(Transient)
	USoundCue* ImpactSound = nullptr;

	UPROPERTY()
	float DestroyTime = 2.f;

	UPROPERTY()
	float CurrentTime = 0.f;

	UPROPERTY()
	bool bHit = false;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	class UDataTable* ProjectileDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	EProjectileType ProjectileType = EProjectileType::EPT_DefaultBullet;

	FProjectileData* SetDataRow(const FName& Name);

	FName GetDataRowName(EProjectileType Type);

	void SetProjectileParams();

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	void FireInDirection(const FVector& ShootDirection);
};
