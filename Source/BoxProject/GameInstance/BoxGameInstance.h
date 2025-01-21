// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BoxGameInstance.generated.h"

class USaves;
class APlayerPawn;

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UBoxGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	virtual void Init() override;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	TArray<FName> Levels;

	UPROPERTY()
	FName CurrentLevel = "None";

	UPROPERTY()
	int32 LevelCount = 0;

	UPROPERTY()
	int32 PlayerLevel = 1;

	UPROPERTY()
	float Experience = 0.f;

	UPROPERTY()
	float MaxExperience = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	int32 StartPlayerLives = 3;

	UPROPERTY()
	int32 PlayerLives = 3;

	UPROPERTY()
	int32 CurrentPlayerLives = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float PercentIncrease = 25;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float MaxHealth = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float ShieldTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float ProjectileTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float EnergyTime = 0.f;

	UPROPERTY()
	float NewMaxHealth = 0.f;

	UPROPERTY()
	float NewShieldTime = 0.f;

	UPROPERTY()
	float NewProjectileTime = 0.f;

	UPROPERTY()
	float NewEnergyTime = 0.f;

	UPROPERTY()
	FString SaveSlot = "GameData";

	UPROPERTY(Transient)
	USaves* SaveData = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Saves")
	TSubclassOf<USaves> SaveClass;

	UPROPERTY()
	TMap<FName, float> LevelsBestTime;

public:
	UPROPERTY()
	bool bSaveGame = false;

	UPROPERTY(BlueprintReadOnly, Category = "GameSettings")
	float RotatePlayerSpeed = 5.f;

	UPROPERTY(BlueprintReadOnly, Category = "GameSettings")
	float MusicVolumValue = 1.f;

	FName GetNextLevel();

	UFUNCTION(BlueprintCallable)
	void StartGameFromBegin();

	void SetExperience(const float Exp);

	void UpdatePlayerStatsHUD();

	bool CheckLevelUp();

	void LevelUp();

	void SaveGameDate();

	USaves* LoadGameData();

	void LoadGame();

	void LoadPlayerStats(APlayerPawn* Player);

	void UpdateElimPlayerStats(APlayerPawn* Player);

	void DecreasePlayerLives();

	void UpdateRotatePlayerSpeed(const float Value);

	FORCEINLINE void UpdateMusicVolume(float Value) { MusicVolumValue = Value; }

	FORCEINLINE float GetPercentIncrease() const { return PercentIncrease; }
	
	FORCEINLINE int32 GetPlayerLives() const { return PlayerLives; }
	FORCEINLINE void SetPlayerLives(const int32 Lives) { PlayerLives = Lives; }

	FORCEINLINE int32 GetCurrentPlayerLives() const { return CurrentPlayerLives; }
	FORCEINLINE void SetCurrentPlayerLives(const int32 Lives) { CurrentPlayerLives = Lives; }

	FORCEINLINE int32 GetPlayerLevel() const { return PlayerLevel; }
	FORCEINLINE FName GetCurrentLevel() const { return Levels[LevelCount]; }
	FORCEINLINE int32 GetLevelNumber() const { return LevelCount; }

	//Player Stats
	FORCEINLINE void SetMaxHealth(float Health) { NewMaxHealth = Health; }
	FORCEINLINE float GetMaxHealth() const { return NewMaxHealth; }
	
	FORCEINLINE float GetShieldTime() const { return NewShieldTime; }
	FORCEINLINE void SetShieldTime(const int32 Time) { NewShieldTime = Time; }
	
	FORCEINLINE float GetEnergyTime() const { return NewEnergyTime; }
	FORCEINLINE void SetEnergyTime(const int32 Time) { NewEnergyTime = Time; }
	
	FORCEINLINE float GetProjectileTime() const { return NewProjectileTime; }
	FORCEINLINE void SetProcjetileTime(const int32 Time) { NewProjectileTime = Time; }

	FORCEINLINE TMap<FName, float> GetLevelsBestTime() const { return LevelsBestTime; };
	FORCEINLINE void SetLevelsBestTime(TMap<FName, float> BestTimes) {LevelsBestTime = BestTimes;}
};
