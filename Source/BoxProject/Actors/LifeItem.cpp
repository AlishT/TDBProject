// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeItem.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"
#include "BoxProject/Controllers/BasePlayerController.h"

void ALifeItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(PlayerClass)) return;

	PlayPickUpSound();

	UBoxGameInstance* GameInstance = GetGameInstance<UBoxGameInstance>();

	if (GameInstance)
	{
		int32 Lives = GameInstance->GetPlayerLives();
		GameInstance->SetPlayerLives(++Lives);

		int32 CurrentLives = GameInstance->GetCurrentPlayerLives();
		GameInstance->SetCurrentPlayerLives(++CurrentLives);

		GameInstance->UpdatePlayerStatsHUD();
	}

	Destroy();
}
