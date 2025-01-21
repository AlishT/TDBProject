// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxProject/ProjectileType.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UBoxComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class BOXPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "CollisionBox")
	UBoxComponent* CollisionBox = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "ItemMesh")
	UStaticMeshComponent* ItemMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "NiagaraSystem")
	UNiagaraSystem* ItemSystem = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* PickUpSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "ItemMesh")
	bool bRotatedMesh = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "ItemMesh")
	float RotateValue = 0.f;
	
	UPROPERTY()
	float NewRotateValue = 0.f;

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PlayPickUpSound();
};
