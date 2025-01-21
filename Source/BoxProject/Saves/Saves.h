// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Saves.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API USaves : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(SaveGame)
	TMap<FName, float> LevelsBestTime;

	UPROPERTY()
	int32 PlayerLevel = 0;

	UPROPERTY()
	int32 PlayerLives = 0;

	UPROPERTY()
	FName CurrentLevel = "None";

	UPROPERTY()
	int32 LevelCount = 0;

	UPROPERTY()
	float CurrentExp = 0.f;

	UPROPERTY()
	float MaxExp = 0.f;

	UPROPERTY()
	float MaxHealth = 0.f;

	UPROPERTY()
	float ShieldTime = 0.f;

	UPROPERTY()
	float ProjectileTime = 0.f;

	UPROPERTY()
	float EnergyTime = 0.f;

	UPROPERTY()
	bool bSaveGame = false;

	UPROPERTY()
	float RotatePlayerSpeed = 0.f;

	UPROPERTY()
	float MusicVolumValue = 1.f;
};
