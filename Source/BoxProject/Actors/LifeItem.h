// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "LifeItem.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API ALifeItem : public AItem
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "PlayerClass")
	TSubclassOf<APawn> PlayerClass;

public:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
