// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/Controllers/BasePlayerController.h"

void UPauseMenu::NativeConstruct()
{
	if (Return)
	{
		Return->OnClicked.AddDynamic(this, &UPauseMenu::OnReturn);
	}

	if (Settings)
	{
		Settings->OnClicked.AddDynamic(this, &UPauseMenu::OnSettings);
	}

	if (Quit)
	{
		Quit->OnClicked.AddDynamic(this, &UPauseMenu::OnQuit);
	}
}

void UPauseMenu::OnReturn()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	
	ABasePlayerController* PlayerController = GetOwningPlayer<ABasePlayerController>();
	
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		SetVisibility(ESlateVisibility::Hidden);
		PlayerController->AddMoving();
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetPause(false);
		PlayerController->bPauseMenu = false;
	}
}

void UPauseMenu::OnSettings()
{
	ABasePlayerController* PlayerController = GetOwningPlayer<ABasePlayerController>();

	if (!PlayerController) return;

	PlayerController->OpenSettingnsMenu();

	SetVisibility(ESlateVisibility::Hidden);
}

void UPauseMenu::OnQuit()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}
