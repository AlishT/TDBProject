// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGM.h"
#include "BoxProject/Controllers/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"

void AMainMenuGM::BeginPlay()
{
	Super::BeginPlay();

	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController)
	{
		PlayerController->OpenMainMenu();
	}

	UBoxGameInstance* GameInstance = GetGameInstance<UBoxGameInstance>();

	if (!GameInstance) return;

	GameInstance->LoadGame();
}
