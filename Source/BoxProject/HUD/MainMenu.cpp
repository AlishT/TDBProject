// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/Saves/Saves.h"
#include "BoxProject/Controllers/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UBoxGameInstance>();

	if (Resume)
	{
		Resume->OnClicked.AddDynamic(this, &UMainMenu::OnResume);

		if (!GameInstance->LoadGameData())
		{
			Resume->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (NewGame)
	{
		NewGame->OnClicked.AddDynamic(this, &UMainMenu::OnNewGame);
	}

	if (Settings)
	{
		Settings->OnClicked.AddDynamic(this, &UMainMenu::OnSettings);
	}

	if (QuitGame)
	{
		QuitGame->OnClicked.AddDynamic(this, &UMainMenu::OnQuitGame);
	}
}

void UMainMenu::OnResume()
{
	if (!GameInstance) return;

	GameInstance->LoadGame();
	FName Level = GameInstance->GetCurrentLevel();

	UGameplayStatics::OpenLevel(GetWorld(), Level);
}

void UMainMenu::OnNewGame()
{
	if (!GameInstance) return;

	if (GameInstance->LoadGameData())
	{
		Resume->SetVisibility(ESlateVisibility::Visible);
	}

	GameInstance->StartGameFromBegin();
	
}

void UMainMenu::OnSettings()
{
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!PlayerController) return;
	
	PlayerController->OpenSettingnsMenu();

	SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::OnQuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit,false);
}
