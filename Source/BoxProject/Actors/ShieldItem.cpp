// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldItem.h"
#include "BoxProject/Components/AbilityComponent.h"
#include "BoxProject/Pawn/PlayerPawn.h"

void AShieldItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor->IsA(APlayerPawn::StaticClass()))
	{
		APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

		if (Player && Player->GetAbilityComponent() && !Player->GetAbilityComponent()->CheckShieldActivation())
		{
			Player->GetAbilityComponent()->ActivateShield();
			PlayPickUpSound();
			Destroy();
		}
	}
}
