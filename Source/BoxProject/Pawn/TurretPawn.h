// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "TurretPawn.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API ATurretPawn : public AEnemyPawn
{
	GENERATED_BODY()
	
public:
	ATurretPawn();

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	UStaticMeshComponent* TurretMesh = nullptr;

	float CurrentRotateValue = 0.f;

public:
	UPROPERTY(EditAnywhere, Category = "Default", meta = (Units = "Degrees"))
	float RotateValue = 0.f;

	virtual void Tick(float DeltaTime) override;

	virtual void RotateToTarget(FVector& TargetLocation) override;

	virtual void Shoot(FVector& TargetLocation) override;

	void RotateTurret();
};
