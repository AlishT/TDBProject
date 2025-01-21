// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LazerBarrier.h"
#include "LazerGate.generated.h"

class UBoxComponent;
class UGateMeshComponent;
class UWidgetComponent;

UCLASS()
class BOXPROJECT_API ALazerGate : public ALazerBarrier
{
	GENERATED_BODY()
	
public:	
	ALazerGate();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UGateMeshComponent* LeftGateMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UGateMeshComponent* RightGateMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "HealthBarComponent")
	UWidgetComponent* LeftHealthBar = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "HealthBarComponent")
	UWidgetComponent* RightHealthBar = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "LazerColor")
	FName LazerParamName = "Color";

	UPROPERTY(EditDefaultsOnly, Category = "LazerColor")
	FColor LazerColor = FColor::Red;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	UBoxComponent* CollisionBox = nullptr;

	void LazerColorChenged();

	UFUNCTION()
	void OnWarningZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
