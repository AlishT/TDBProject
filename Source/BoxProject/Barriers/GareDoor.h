// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GareDoor.generated.h"

class UBoxComponent;

UCLASS()
class BOXPROJECT_API AGareDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGareDoor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
private:
    UPROPERTY(EditAnywhere,Category = "Default")
    UBoxComponent* DoorTriger = nullptr;

	UPROPERTY(EditAnywhere,Category = "Default")
	UStaticMeshComponent* DoorMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly,Category = "Default")
	TSubclassOf<APawn> PlayerClass;

	UPROPERTY()
	bool bDoorActivate = false;

	UPROPERTY()
	bool bTrigerActivate = false;

	UPROPERTY()
	float OpenDoorTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Default")
	float Speed = 0.f;

	UPROPERTY()
	float CurrentTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Default")
	float Distance = 0.f;

	UPROPERTY()
	float Progress = 0.f;

	UPROPERTY(EditAnywhere, Category = "Default")
	TArray<class AEnemyPawn*> EnemyPawns;

	UPROPERTY()
	int32 EnemyCount = 0;

	UPROPERTY()
	FVector StarLocation = FVector::ZeroVector;

	UPROPERTY()
	FVector EndLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Default")
	FVector MovingDirection = FVector::ZeroVector;

	bool EnemiesChecked();

	void OpenDoor();

	FVector MovengDoor();

	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
