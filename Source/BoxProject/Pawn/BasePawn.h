// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UFloatingPawnMovement;
class UCombatComponent;
class UHealthComponent;
class USoundCue;

UCLASS()
class BOXPROJECT_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Capsule")
	UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "BaseMesh")
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Capsule")
	UFloatingPawnMovement* PawnMovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "CombatComponent")
	UCombatComponent* Combat = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "CombatComponent")
	UHealthComponent* HealthComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "SpawnPosition")
	USceneComponent* FrontWeaponMuzzle = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "SpawnPosition")
	USceneComponent* RightWeaponMuzzle = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "SpawnPosition")
	USceneComponent* LeftWeaponMuzzle = nullptr;

	UPROPERTY()
	TArray<USceneComponent*> Weapons;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	USoundCue* ElimSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UParticleSystem* ElimEffect = nullptr;

	UPROPERTY()
	bool bElimPawn = false;

	UFUNCTION()
	void EliminationHandler(float Health);

public:
	FORCEINLINE TArray<USceneComponent*> GetWeapons() const { return Weapons; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCombatComponent* GetCombat() const { return Combat; }
	FORCEINLINE UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }
	FORCEINLINE UStaticMeshComponent* GetBaseMesh() const { return BaseMesh; }
	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	FORCEINLINE UFloatingPawnMovement* GetPawnMovement() const { return PawnMovementComponent; }
	FORCEINLINE bool IsElimPawn() const { return bElimPawn; }
	FORCEINLINE USceneComponent* GetFrontWeaponMuzzle() const { return FrontWeaponMuzzle; }
};
