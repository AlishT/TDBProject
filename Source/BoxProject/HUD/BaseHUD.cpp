// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "BoxProject/HUD/PlayerOverlay.h"
#include "Components/TextBlock.h"

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseHUD::AddPlayerOverlay()
{
	APlayerController* PlayerContraler = GetOwningPlayerController();

	if (PlayerContraler && PlayerOverlayClass)
	{
		PawnOverlay = CreateWidget<UPlayerOverlay>(PlayerContraler, PlayerOverlayClass);

		if (PawnOverlay)
		{
			PawnOverlay->AddToViewport();
			PawnOverlay->CkeckpointText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
