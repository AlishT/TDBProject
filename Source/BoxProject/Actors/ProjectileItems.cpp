// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileItems.h"
#include "Components/BoxComponent.h"
#include "BoxProject/Pawn/BasePawn.h"
#include "BoxProject/Components/CombatComponent.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"

void AProjectileItems::BeginPlay()
{
	Super::BeginPlay();

	SetItemType();
}

void AProjectileItems::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(PlayerClass))
	{
		PlayPickUpSound();

		ABasePawn* Player = Cast<ABasePawn>(OtherActor);

		if (Player && Player->GetCombat())
		{
			Player->GetCombat()->SetWeaponsParams(ProjectileType);
			Player->GetCombat()->SetProjectileType(ProjectileType);

			if (ItemClasses.Contains(ProjectileType))
			{
				Player->GetCombat()->SetProjectileClass(ItemClasses[ProjectileType]);
			}
		}

		Destroy();
	}
}

void AProjectileItems::SetItemType()
{
	UBoxGameInstance* GameInstance = GetGameInstance<UBoxGameInstance>();

	if (!GameInstance) return;

	//temporary decision - small count of levels
	switch (GameInstance->GetLevelNumber())
	{
	case 0:
	case 1:
	case 2:
		ProjectileType = GetRandomItemType(MinItemTypes);
		break;
	case 3:
	case 4:
	case 5:
		ProjectileType = GetRandomItemType(AverageItemTypes);
		break;
	case 6:
	case 7:
	case 8:
		ProjectileType = GetRandomItemType(MaxItemTypes);
		break;
	}
}

EProjectileType AProjectileItems::GetRandomItemType(const TArray<EProjectileType> ItemTypes)
{
	int ItemNumber = FMath::RandRange(1, ItemTypes.Num() - 1);
	UE_LOG(LogTemp, Warning, TEXT("ItemTypes.Num(): %f"), ItemNumber);

	return ItemTypes[ItemNumber];
}
