// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LazerBarrier.generated.h"

class UBoxComponent;

UCLASS()
class BOXPROJECT_API ALazerBarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	ALazerBarrier();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UStaticMeshComponent* LazerMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UBoxComponent* LazerCollision = nullptr;

	UPROPERTY(EditAnywhere, Category = "Default")
	float LazerActiveTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Default")
	float LazerDeactiveTime = 0.f;

	UPROPERTY()
	float CurrentTime = 0.f;

	UPROPERTY()
	bool bLazerActive = true;

	UPROPERTY(EditAnywhere, Category = "Default")
	float Damage = 500.f;

	UFUNCTION()
	void OnLazerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<APawn> PlayerClass;

	FORCEINLINE UStaticMeshComponent* GetLazerMesh() const { return LazerMesh; }
	FORCEINLINE UBoxComponent* GetLazerCollision() const { return LazerCollision; }
};
