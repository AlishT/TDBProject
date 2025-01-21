// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelEnd.generated.h"

class UBoxComponent;

UCLASS()
class BOXPROJECT_API ALevelEnd : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelEnd();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	UBoxComponent* CollisionBox = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TSubclassOf<APawn> PlayerClass;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
