// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BaseGameMode.generated.h"

class AEnemyPawn;
class UBoxGameInstance;
class USoundCue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerElim, bool, bIsElim);

/**
 * 
 */
UCLASS()
class BOXPROJECT_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TSubclassOf<AActor> ProjectileItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TSubclassOf<AActor> HealItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TSubclassOf<AActor> ShieldItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Items")
	TSubclassOf<AActor> EnergyItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "PawnClass")
	TSubclassOf<AActor> PlayerClass;

	UPROPERTY(Transient)
	AEnemyPawn* EnemyPawn = nullptr;

	UPROPERTY(Transient)
	UBoxGameInstance* GameInstance = nullptr;

	UPROPERTY()
	int32 SpawnChance = 10;

	UPROPERTY()
	FTransform SpawnLocation;

	UPROPERTY()
	FRotator PawnRotation = FRotator::ZeroRotator;

	UPROPERTY()
	int32 ElimEnemiesCount = 0;

	UPROPERTY()
	int32 EnemiesNumber = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float StartPlayTime = 0.f;

	UPROPERTY()
	float LevelTime = 0.f;

	UPROPERTY()
	float BestLevelTime = 0.f;

	UPROPERTY()
	bool bLevelEnd = false;

	UPROPERTY()
	bool bPlayerElim = false;

	UPROPERTY(EditDefaultsOnly, Category = "Music")
	USoundCue* LevelMusic = nullptr;

	UPROPERTY()
	TArray<AActor*> AllEnemis;

	void GetItem(TSubclassOf<AActor> ItemClass);

	void SpawnRandomItem();

	void PlayerElimHandler(APawn* ElimPawn);

	void EnemyElimHandler(APawn* ElimPawn);

	void UpdatePlayerStats();

	void StartLeveTimer(float DeltaTime);

public:
	UPROPERTY()
	FOnPlayerElim OnPlayerElim;

	virtual void Tick(float DeltaTime) override;

	void PawnElimHandler(APawn* ElimPawn);

	UFUNCTION(BlueprintCallable)
	void OpenNextLevel();

	UFUNCTION(BlueprintCallable)
	void OpenStatisticMenu();
	
	UFUNCTION(BlueprintCallable)
	void RestartLevel();

	void ResetLevelTime();

	FORCEINLINE void SetSpawnLocation(const FTransform& Transform) { SpawnLocation = Transform; }
	FORCEINLINE void SetPawnRotation(const FRotator& Rotation) { PawnRotation = Rotation; }

};
