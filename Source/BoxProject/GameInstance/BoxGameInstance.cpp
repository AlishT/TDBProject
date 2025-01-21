// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/Controllers/BasePlayerController.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "BoxProject/Saves/Saves.h"
#include "BoxProject/Components/HealthComponent.h"
#include "BoxProject/Components/AbilityComponent.h"
#include "BoxProject/Components/CombatComponent.h"

void UBoxGameInstance::Init()
{
	Super::Init();
}

FName UBoxGameInstance::GetNextLevel()
{	
	LevelCount++;
	
	if (LevelCount < Levels.Num())
	{
		return Levels[LevelCount];
	}

	LevelCount = 0;

	return Levels[LevelCount];
}

void UBoxGameInstance::StartGameFromBegin()
{
	LevelCount = 0;
	//bSaveGame = true;
	PlayerLives = StartPlayerLives;
	Experience = 0.f;
	MaxExperience = 1000.f;
	CurrentLevel = Levels[LevelCount];
	PlayerLevel = 1;
	NewMaxHealth = MaxHealth;
	NewShieldTime = ShieldTime;
	NewProjectileTime = ProjectileTime;
	NewEnergyTime = EnergyTime;

	SaveGameDate();

	UGameplayStatics::OpenLevel(this, CurrentLevel);
}

void UBoxGameInstance::SetExperience(const float Exp)
{
	Experience += Exp;

	if (CheckLevelUp())
	{
		LevelUp();
	}

	UpdatePlayerStatsHUD();
}

void UBoxGameInstance::UpdatePlayerStatsHUD()
{
	ABasePlayerController* Controller = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (Controller)
	{
		Controller->SetExpHUD(MaxExperience, Experience);
		Controller->SetPlayerStatsHUD(PlayerLevel, GetCurrentPlayerLives());
	}
}

bool UBoxGameInstance::CheckLevelUp()
{
	return Experience >= MaxExperience;
}

void UBoxGameInstance::LevelUp()
{
	ABasePlayerController* Controller = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!Controller) return;

	APlayerPawn* Player = Controller->GetPawn<APlayerPawn>();

	if (Player)
	{
		Player->IncreasePlayerStats(PercentIncrease, this);
		Player->ShowLevelUpSystem();
	}

	Experience = 0.f;

	PlayerLevel++;

	MaxExperience += MaxExperience * PercentIncrease / 100;
}

void UBoxGameInstance::SaveGameDate()
{
	if (!SaveClass) return;

	SaveData = Cast<USaves>(UGameplayStatics::CreateSaveGameObject(SaveClass));
	
	//bSaveGame = true;

	if (SaveData)
	{
		SaveData->PlayerLevel = PlayerLevel;
		SaveData->CurrentLevel = CurrentLevel;
		SaveData->LevelCount = LevelCount;
		SaveData->PlayerLives = PlayerLives;
		SaveData->CurrentExp = Experience;
		SaveData->MaxExp = MaxExperience;
		SaveData->MaxHealth = NewMaxHealth;
		SaveData->ShieldTime = NewShieldTime;
		SaveData->ProjectileTime = NewProjectileTime;
		SaveData->EnergyTime = NewEnergyTime;
		SaveData->LevelsBestTime = LevelsBestTime;
		SaveData->RotatePlayerSpeed = RotatePlayerSpeed;
		SaveData->MusicVolumValue = MusicVolumValue;

		UGameplayStatics::SaveGameToSlot(SaveData, SaveSlot, 0);
	}
}

USaves* UBoxGameInstance::LoadGameData()
{
	if (!SaveData)
	{
		return SaveData = Cast<USaves>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	}

	return SaveData;
}

void UBoxGameInstance::LoadGame()
{
	SaveData = (SaveData) ? SaveData : LoadGameData();

	if (SaveData)
	{
		PlayerLevel = SaveData->PlayerLevel;
		CurrentLevel = SaveData->CurrentLevel;
		LevelCount = SaveData->LevelCount;
		PlayerLives = SaveData->PlayerLives;
		Experience = SaveData->CurrentExp;
		MaxExperience = SaveData->MaxExp;
		NewMaxHealth = SaveData->MaxHealth;
		NewShieldTime = SaveData->ShieldTime;
		NewProjectileTime = SaveData->ProjectileTime;
		NewEnergyTime = SaveData->EnergyTime;
		LevelsBestTime = SaveData->LevelsBestTime;
		RotatePlayerSpeed = SaveData->RotatePlayerSpeed;
		MusicVolumValue = SaveData->MusicVolumValue;
	}
}

void UBoxGameInstance::LoadPlayerStats(APlayerPawn* Player)
{
	if (!Player) return;

	SaveData = (SaveData) ? SaveData : LoadGameData();

	CurrentPlayerLives = PlayerLives;

	Player->SetRotationSpeed(RotatePlayerSpeed);

	if (Player->GetHealthComponent())
	{
		NewMaxHealth = SaveData->MaxHealth;
		Player->GetHealthComponent()->SetMaxHealth(NewMaxHealth);
		Player->GetHealthComponent()->UpdateCurrentHealth();
	}

	if (Player->GetCombat())
	{
		NewProjectileTime = SaveData->ProjectileTime;
		Player->GetCombat()->SetProjectileTime(NewProjectileTime);
	}

	if (Player->GetAbilityComponent())
	{
		NewShieldTime = SaveData->ShieldTime;
		NewEnergyTime = SaveData->EnergyTime;

		Player->GetAbilityComponent()->SetShieldTime(NewShieldTime);
		Player->GetAbilityComponent()->SetEnergyTime(NewEnergyTime);
	}
}

void UBoxGameInstance::UpdateElimPlayerStats(APlayerPawn* Player)
{
	if (!Player) return;

	Player->SetRotationSpeed(RotatePlayerSpeed);

	if (Player->GetHealthComponent())
	{
		Player->GetHealthComponent()->SetMaxHealth(NewMaxHealth);
		Player->GetHealthComponent()->UpdateCurrentHealth();
	}

	if (Player->GetCombat())
	{
		Player->GetCombat()->SetProjectileTime(NewProjectileTime);
	}

	if (Player->GetAbilityComponent())
	{
		Player->GetAbilityComponent()->SetShieldTime(NewShieldTime);
		Player->GetAbilityComponent()->SetEnergyTime(NewEnergyTime);
	}
}

void UBoxGameInstance::DecreasePlayerLives()
{
	CurrentPlayerLives--;
	UpdatePlayerStatsHUD();
}

void UBoxGameInstance::UpdateRotatePlayerSpeed(const float Value)
{
	RotatePlayerSpeed = Value;

	APlayerPawn* Player = GetFirstLocalPlayerController()->GetPawn<APlayerPawn>();
	if (Player)
	{
		Player->SetRotationSpeed(RotatePlayerSpeed);
	}
}


