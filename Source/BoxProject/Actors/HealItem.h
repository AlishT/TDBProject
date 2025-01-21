// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealItem.generated.h"

class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class BOXPROJECT_API AHealItem : public AItem
{
	GENERATED_BODY()

private:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "NiagaraSystem")
	UNiagaraSystem* HealSystem = nullptr;
};
