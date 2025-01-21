// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LazerBarrier.h"
#include "RotatedBarrier.generated.h"

class UBoxComponent;
class UBarrierMovementComponent;
class USoundCue;

UCLASS()
class BOXPROJECT_API ARotatedBarrier : public ALazerBarrier
{
	GENERATED_BODY()
	
public:	
	ARotatedBarrier();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UStaticMeshComponent* LazerRotatorMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UBarrierMovementComponent* BarrierMovement = nullptr;

	UPROPERTY(EditAnywhere, Category = "Default")
	float RotateSpeed = 3.f;

	UPROPERTY()
	float Direction = 1.f;

	UPROPERTY(EditAnywhere, Category = "Default")
	bool bRotateRight = true;

	UPROPERTY(EditAnywhere, Category = "Default")
	USoundCue* LazerSound = nullptr;

	void RotateLazer();
};
