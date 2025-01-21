// Fill out your copyright notice in the Description page of Project Settings.


#include "Options.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "BoxProject/Controllers/BasePlayerController.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"

void UOptions::NativeConstruct()
{
	if (Back)
	{
		Back->OnClicked.AddDynamic(this, &UOptions::OnBack);
	}

	if (RotateSlider)
	{
		RotateSlider->OnValueChanged.AddDynamic(this, &UOptions::OnRatateValueChanged);
	}

	if (MusicSlider)
	{
		MusicSlider->OnValueChanged.AddDynamic(this, &UOptions::OnMusicValueChanged);
	}

	BoxGameInstance = GetGameInstance<UBoxGameInstance>();
}

void UOptions::OnBack()
{
	ABasePlayerController* PlayerController = GetOwningPlayer<ABasePlayerController>();

	if (!PlayerController) return;

	if (PlayerController->bMainMenu)
	{
		PlayerController->OpenMainMenu();
	}
	else
	{
		PlayerController->OpenPauseMenu();
	}

	BoxGameInstance = (BoxGameInstance) ? BoxGameInstance : GetGameInstance<UBoxGameInstance>();

	if (BoxGameInstance && BoxGameInstance->LoadGameData())
	{
		BoxGameInstance->SaveGameDate();
	}

	RemoveFromParent();
}

void UOptions::OnRatateValueChanged(float Value)
{
	BoxGameInstance = (BoxGameInstance) ? BoxGameInstance : GetGameInstance<UBoxGameInstance>();

	if (!BoxGameInstance) return;

	BoxGameInstance->UpdateRotatePlayerSpeed(Value);
	
}

void UOptions::OnMusicValueChanged(float Value)
{
	BoxGameInstance = (BoxGameInstance) ? BoxGameInstance : GetGameInstance<UBoxGameInstance>();

	if (!BoxGameInstance) return;

	BoxGameInstance->UpdateMusicVolume(Value);
}

