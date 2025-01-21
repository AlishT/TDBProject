// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerOverlay.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/Controllers/BasePlayerController.h"

void UPlayerOverlay::NativeConstruct()
{
	if (Pause)
	{
		Pause->OnClicked.AddDynamic(this, &UPlayerOverlay::OnPause);
	}
}

void UPlayerOverlay::OnPause()
{

	ABasePlayerController* PlayerControler = GetOwningPlayer<ABasePlayerController>();

	if (PlayerControler)
	{
		if (PlayerControler->bPauseMenu) return;

		PlayerControler->OpenPauseMenu();

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
