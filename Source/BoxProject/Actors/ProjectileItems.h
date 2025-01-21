// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ProjectileItems.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API AProjectileItems : public AItem
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	EProjectileType ProjectileType = EProjectileType::EPT_DefaultBullet;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TArray<EProjectileType> MinItemTypes;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TArray<EProjectileType> AverageItemTypes;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TArray<EProjectileType> MaxItemTypes;

	//UPROPERTY()
	//int32 ItemNumber = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TMap<EProjectileType, TSubclassOf<AActor>> ItemClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<APawn> PlayerClass;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetItemType();

	EProjectileType GetRandomItemType(const TArray<EProjectileType> ItemTypes);

};
