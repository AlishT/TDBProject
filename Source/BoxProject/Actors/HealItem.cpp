// Fill out your copyright notice in the Description page of Project Settings.


#include "HealItem.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "BoxProject/Components/HealthComponent.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraFunctionLibrary.h"

void AHealItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor->IsA(APlayerPawn::StaticClass()))
	{
		APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor);

		if (!PlayerPawn && PlayerPawn->GetHealthComponent()) return;
		
		if (HealSystem)
		{
			UNiagaraFunctionLibrary::SpawnSystemAttached(HealSystem, PlayerPawn->GetRootComponent(), FName(), PlayerPawn->GetActorLocation(), PlayerPawn->GetActorRotation(), EAttachLocation::KeepWorldPosition, false);
		}

		PlayPickUpSound();

		PlayerPawn->GetHealthComponent()->UpdateCurrentHealth();

		Destroy();
		
	}
}
