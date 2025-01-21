// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevelMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/GameMode/BaseGameMode.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"

void UEndLevelMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (NextLevel)
	{
		NextLevel->OnClicked.AddDynamic(this, &UEndLevelMenu::OnNextLevel);
	}

	if (RestartLevel)
	{
		RestartLevel->OnClicked.AddDynamic(this, &UEndLevelMenu::OnRestart);
	}
}

void UEndLevelMenu::OnNextLevel()
{
	ABaseGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();
	if (GameMode)
	{
		GameMode->OpenStatisticMenu();
	}
}

void UEndLevelMenu::OnRestart()
{
	ABaseGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();
	if (GameMode)
	{
		GameMode->RestartLevel();
		GameMode->ResetLevelTime();
	}

}
