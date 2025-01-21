// Fill out your copyright notice in the Description page of Project Settings.


#include "ElimMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/GameMode/BaseGameMode.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"
#include "BoxProject/Saves/Saves.h"

void UElimMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenu)
	{
		MainMenu->OnClicked.AddDynamic(this, &UElimMenu::OnMenu);
	}

	if (RestartLevel)
	{
		RestartLevel->OnClicked.AddDynamic(this, &UElimMenu::OnRestart);
	}
}

void UElimMenu::OnMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

void UElimMenu::OnRestart()
{
	ABaseGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();
	if (GameMode)
	{
		GameMode->RestartLevel();
		GameMode->ResetLevelTime();
	}

}
