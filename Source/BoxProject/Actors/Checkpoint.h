// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class BOXPROJECT_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckpoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	UBoxComponent* CollisionBox = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UPaperSpriteComponent* CheckpointTransform = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerClass")
	TSubclassOf<AActor> PlayerClass;

	UPROPERTY()
	bool bActivate = false;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
