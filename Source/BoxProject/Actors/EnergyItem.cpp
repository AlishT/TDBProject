// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyItem.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "BoxProject/Components/AbilityComponent.h"

void AEnergyItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPawn::StaticClass()))
	{
		APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

		bool bEnergyActive = Player && Player->GetAbilityComponent() && !Player->GetAbilityComponent()->CheckEnergyActivation();

		if (bEnergyActive)
		{
			PlayPickUpSound();
			Player->GetAbilityComponent()->ActivateEnergy();
			Destroy();
		}
	}
}
