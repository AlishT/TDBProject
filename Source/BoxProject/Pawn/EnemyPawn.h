// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyPawn.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class BOXPROJECT_API AEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	AEnemyPawn();

private:
	UPROPERTY(EditAnywhere, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditAnywhere, Category = "Default")
	float InterpRotateSpeed = 0.f;

	UPROPERTY(EditAnywhere, Category = "Default", meta = (Units = "Degrees"))
	float TurretAimError = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "HealthBarComponent")
	UWidgetComponent* HealthBar = nullptr;

	UPROPERTY()
	float ElimExp = 0.f;

	UPROPERTY()
	bool bLostDoorKey = false;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetEnemyProgressBar(float CurrentHealth, float MaxHealth);

	UFUNCTION()
	virtual void RotateToTarget(FVector& TargetLocation);

	UFUNCTION()
	virtual void Shoot(FVector& TargetLocation);

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	FORCEINLINE float GetInterpRotateSpeed() const { return InterpRotateSpeed; }
	FORCEINLINE float GetTurretAimError() const { return TurretAimError; }
	FORCEINLINE float GetElimExp() const { return ElimExp; }
	FORCEINLINE bool IsLostDoorKey() const { return bLostDoorKey; }
	FORCEINLINE void SetLostDoorKey(const bool bKey) { bLostDoorKey = bKey; }
};
