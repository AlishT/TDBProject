// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"
#include "BoxProject/Pawn/EnemyPawn.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "BoxProject/Pawn/EnemyPawn.h"
#include "BoxProject/Controllers/BasePlayerController.h"
#include "BoxProject/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"
#include "BoxProject/Saves/Saves.h"
#include "Sound/SoundCue.h"

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (LevelMusic)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), LevelMusic);
	}

	for (TActorIterator<APlayerStart> PlayerStartItr(GetWorld()); PlayerStartItr; ++PlayerStartItr)
	{
		SpawnLocation = PlayerStartItr->GetActorTransform();
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyPawn::StaticClass(), AllEnemis);

	EnemiesNumber = AllEnemis.Num();

	GameInstance = GetGameInstance<UBoxGameInstance>();

	UpdatePlayerStats();
}

void ABaseGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StartLeveTimer(DeltaTime);
}

void ABaseGameMode::PawnElimHandler(APawn* ElimPawn)
{
	if (!ElimPawn) return;
	
	if (ElimPawn->IsA(PlayerClass))
	{
		PlayerElimHandler(ElimPawn);
	}
	else
	{
		EnemyElimHandler(ElimPawn);
	}
}

void ABaseGameMode::PlayerElimHandler(APawn* ElimPawn)
{
	ABasePlayerController* PlayerController = ElimPawn->GetController<ABasePlayerController>();

	if (GameInstance && PlayerController)
	{
		GameInstance->DecreasePlayerLives();

		if (GameInstance->GetCurrentPlayerLives() <= 0)
		{
			APlayerPawn* PlayerPawn = Cast<APlayerPawn>(ElimPawn);
			
			if (PlayerPawn)
			{
				PlayerPawn->GetBaseMesh()->SetVisibility(false);
				PlayerPawn = nullptr;
				bPlayerElim = true;

				OnPlayerElim.Broadcast(bPlayerElim);
			}
			
			PlayerController->OpenElimMenu();
			
			return;
		}

		ElimPawn->Destroy();
		APlayerPawn* NewPlayerPawn = GetWorld()->SpawnActor<APlayerPawn>(PlayerClass, SpawnLocation);
			
		if (NewPlayerPawn && NewPlayerPawn->GetHealthComponent())
		{
			PlayerController->Possess(NewPlayerPawn);
			NewPlayerPawn->SetActorRotation(PawnRotation);
			GameInstance->UpdateElimPlayerStats(NewPlayerPawn);
			NewPlayerPawn->GetHealthComponent()->UpdatePlayerHealthHUD();
		}
	}
}

void ABaseGameMode::EnemyElimHandler(APawn* ElimPawn)
{
	EnemyPawn = Cast<AEnemyPawn>(ElimPawn);

	SpawnRandomItem();

	if (GameInstance && EnemyPawn)
	{
		float Exp = EnemyPawn->GetElimExp();
		GameInstance->SetExperience(Exp);
	}

	ElimEnemiesCount++;

	ElimPawn->Destroy();
}

void ABaseGameMode::UpdatePlayerStats()
{
	if (!GameInstance) return;
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (!PlayerController) return;
	
	APlayerPawn* Player = Cast<APlayerPawn>(PlayerController->GetPawn());
	
	if (Player)
	{
		if (GameInstance->LoadGameData())
		{
			GameInstance->LoadPlayerStats(Player);
		}

		Player->UpdatePlayerStats(GameInstance);
	}
}

void ABaseGameMode::StartLeveTimer(float DeltaTime)
{
	if (bLevelEnd) return;
	LevelTime += DeltaTime;
}

void ABaseGameMode::GetItem(TSubclassOf<AActor> ItemClass)
{
	if (!EnemyPawn) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = EnemyPawn;
	SpawnParams.Instigator = EnemyPawn->GetInstigator();

	FVector Location = EnemyPawn->GetActorLocation();
	FRotator Rotation = EnemyPawn->GetActorRotation();

	GetWorld()->SpawnActor<AActor>(ItemClass, Location, Rotation, SpawnParams);
}

void ABaseGameMode::SpawnRandomItem()
{
	const int32 Value = FMath::RandRange(1, SpawnChance);
			
	switch (Value)
	{
	case 2:
	case 6:
		break;
	case 7:
		GetItem(EnergyItemClass);
		break;
	case 3:
	case 5:
	case 8:
	case 10:
		GetItem(ProjectileItemClass);
		break;
	case 4:
	case 1:
		GetItem(HealItemClass);
		break;
	case 9:
		GetItem(ShieldItemClass);
		break;
	}
}

void ABaseGameMode::OpenNextLevel()
{
	if (!GameInstance) return;

	FName LevelName = GameInstance->GetCurrentLevel();

	UGameplayStatics::OpenLevel(this, LevelName);

	GameInstance->LoadGame();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
	}
}

void ABaseGameMode::OpenStatisticMenu()
{
	if (GameInstance)
	{
		TMap<FName, float>LevelsBestTime = GameInstance->GetLevelsBestTime();

		FName LevelName = GameInstance->GetCurrentLevel();

		if (!LevelsBestTime.Contains(LevelName))
		{
			LevelsBestTime.Emplace(LevelName, LevelTime);
			GameInstance->SetLevelsBestTime(LevelsBestTime);
		}
		
		if (LevelsBestTime.Contains(LevelName) && LevelTime < LevelsBestTime[LevelName])
		{
			LevelsBestTime[LevelName] = LevelTime;
			GameInstance->SetLevelsBestTime(LevelsBestTime);
		}
			
		BestLevelTime = LevelsBestTime[LevelName];

		GameInstance->GetNextLevel();

		GameInstance->SaveGameDate();
	}

	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		PlayerController->OpenStatisticMenu(LevelTime, BestLevelTime,ElimEnemiesCount, EnemiesNumber);
	}

}

void ABaseGameMode::RestartLevel() 
{
	GameInstance = GetGameInstance<UBoxGameInstance>();

	if (!GameInstance) return;

	GameInstance->LoadGame();

	FName Level = GameInstance->GetCurrentLevel();
	UGameplayStatics::OpenLevel(GetWorld(), Level);
}

void ABaseGameMode::ResetLevelTime()
{
	LevelTime = 0.f;
	bLevelEnd = false;
}
