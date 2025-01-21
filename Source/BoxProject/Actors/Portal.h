// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UBoxComponent;
class USoundCue;

UCLASS()
class BOXPROJECT_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	APortal();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	UBoxComponent* PortalCollision = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UStaticMeshComponent* PortalMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	USoundCue* PortalSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<APawn> PlayerClass;

	UPROPERTY(EditAnywhere,Category = "BehaviorTree", meta = (AllowPrivateAccess = "true", MakeEditWidget = "true"))
	FVector PoltalTargetPoint = FVector::ZeroVector;

	UPROPERTY()
	FVector WorldTargetPoint = FVector::ZeroVector;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

