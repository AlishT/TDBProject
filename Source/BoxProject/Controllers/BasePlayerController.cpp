// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BoxProject/HUD/BaseHUD.h"
#include "BoxProject/HUD/PlayerOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "BoxProject/HUD/StatisticMenuWidget.h"
#include "Components/TextBlock.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	AddMoving();

	BaseHUD = GetHUD<ABaseHUD>();

	if (BaseHUD)
	{
		BaseHUD->AddPlayerOverlay();
	}

	SetInputMode(FInputModeGameOnly());

	UBoxGameInstance* GameInstance = GetGameInstance<UBoxGameInstance>();

	if (GameInstance)
	{
		GameInstance->UpdatePlayerStatsHUD();
	}
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TextVisibility != ESlateVisibility::Hidden)
	{
		CurrentTextVisibilityTime += DeltaTime;

		if (CurrentTextVisibilityTime >= TextVisibilityTime)
		{
			SetCheckpointTextVisible(ESlateVisibility::Hidden);
		}
	}
}

void ABasePlayerController::SetHealthHUD(float MaxHealth, float CurrentHealth)
{
	bool bValidHUD = BaseHUD && BaseHUD->PawnOverlay && BaseHUD->PawnOverlay->HealthBar;

	if (bValidHUD)
	{
		const float HealthPerc = CurrentHealth / MaxHealth;

		BaseHUD->PawnOverlay->HealthBar->SetPercent(HealthPerc);
	}
}

void ABasePlayerController::SetExpHUD(float MaxExp, float Exp)
{
	bool bValidHUD = BaseHUD && BaseHUD->PawnOverlay && BaseHUD->PawnOverlay->ExpBar;

	if (bValidHUD)
	{
		const float ExpPerc = Exp / MaxExp;

		BaseHUD->PawnOverlay->ExpBar->SetPercent(ExpPerc);
	}
}

void ABasePlayerController::SetPlayerStatsHUD(int32 PlayerLevel, int32 PlayerLives)
{
	bool bValidHUD = BaseHUD && BaseHUD->PawnOverlay && BaseHUD->PawnOverlay->LevelCountText && BaseHUD->PawnOverlay->LivesCountText;

	if (bValidHUD)
	{
		FString PlayerLevelText = FString::Printf(TEXT("%d"), PlayerLevel);
		FString PlayerLivesText = FString::Printf(TEXT("%d"), PlayerLives);
		
		BaseHUD->PawnOverlay->LevelCountText->SetText(FText::FromString(PlayerLevelText));
		BaseHUD->PawnOverlay->LivesCountText->SetText(FText::FromString(PlayerLivesText));
	}
}

void ABasePlayerController::SetCheckpointTextVisible(ESlateVisibility Type)
{
	bool bValidHUD = BaseHUD && BaseHUD->PawnOverlay && BaseHUD->PawnOverlay->CkeckpointText;

	if (bValidHUD)
	{
		TextVisibility = Type;
		BaseHUD->PawnOverlay->CkeckpointText->SetVisibility(TextVisibility);

		CurrentTextVisibilityTime = 0.f;
	}

}

void ABasePlayerController::OpenMainMenu()
{
	OpenMenu(MainMenuClass, true);
	bMainMenu = true;
}

void ABasePlayerController::OpenMenu(TSubclassOf<UUserWidget> MenuClass, bool bShowMouse)
{
	if (!MenuClass) return;

	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);

	if (Menu)
	{
		Menu->AddToViewport();
	}

	if (Subsystem)
	{
		Subsystem->RemoveMappingContext(MovingMC);
	}

	SetInputMode(FInputModeUIOnly());

	SetShowMouseCursor(bShowMouse);
}

void ABasePlayerController::OpenEndLevelMenu()
{
	OpenMenu(EndLevelMenuClass, true);
}

void ABasePlayerController::OpenElimMenu()
{
	OpenMenu(ElimMenuClass, true);
}

void ABasePlayerController::OpenLoadingMenu()
{
	//OpenMenu(LoadingMenuClass, false);
}

void ABasePlayerController::OpenStatisticMenu(float CurrentTime, float BestTime, int32 ElinEnemies, int32 Eneimes)
{
	if (!StatisticMenuClass) return;

	UStatisticMenuWidget* StatisticMenu = CreateWidget<UStatisticMenuWidget>(this, StatisticMenuClass);

	if (!StatisticMenu) return;
	
	StatisticMenu->AddToViewport();

	float SecondsInMinute = 60.f;

	if (StatisticMenu->CurrentLevelTime)
	{
		FString CurrentLevelTimeText = FString::Printf(TEXT("%d:%02d"), static_cast<int32>(CurrentTime / SecondsInMinute), FMath::CeilToInt(FMath::Fmod(CurrentTime, SecondsInMinute)));
		StatisticMenu->CurrentLevelTime->SetText(FText::FromString(CurrentLevelTimeText));
	}

	if (StatisticMenu->BestLevelTime)
	{
		FString BestLevelTimeText = FString::Printf(TEXT("%d:%02d"), static_cast<int32>(BestTime / SecondsInMinute), FMath::CeilToInt(FMath::Fmod(BestTime, SecondsInMinute)));
		StatisticMenu->BestLevelTime->SetText(FText::FromString(BestLevelTimeText));
	}

	if(StatisticMenu->ElimEnemiesNum)
	{
		FString ElimEnemiesNumText = FString::Printf(TEXT("%d"), ElinEnemies);
		StatisticMenu->ElimEnemiesNum->SetText(FText::FromString(ElimEnemiesNumText));
	}

	if (StatisticMenu->EnemisNumber)
	{
		FString EnemiesNumberText = FString::Printf(TEXT("%d"), Eneimes);
		StatisticMenu->EnemisNumber->SetText(FText::FromString(EnemiesNumberText));
	}

	//OpenMenu(StatisticMenuClass, true);
}

void ABasePlayerController::OpenPauseMenu()
{
	OpenMenu(PauseMenuClass, true);
	SetPause(true);
	bMainMenu = false;
}

void ABasePlayerController::OpenSettingnsMenu()
{
	OpenMenu(SettingsMenuClass, true);
}

void ABasePlayerController::AddMoving()
{
	if (Subsystem)
	{
		Subsystem->AddMappingContext(MovingMC, 0);
	}
}
