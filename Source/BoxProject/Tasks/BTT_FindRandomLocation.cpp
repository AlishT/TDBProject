// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomLocation.h"
#include "BoxProject/Controllers/EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BoxProject/Pawn/TurretPawn.h"
#include "NavigationSystem.h"

UBTT_FindRandomLocation::UBTT_FindRandomLocation()
{
	NodeName = TEXT("Find Random Location");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UBTT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Super::ExecuteTask(OwnerComp, NodeMemory);
	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

	FNavLocation Location{};

	AEnemyController* AIController = Cast<AEnemyController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		const APawn* AIPawn { AIController->GetPawn() };

		if (AIPawn)
		{
			const FVector Origin = AIPawn->GetActorLocation();

			const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
			
			if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
			{
				AIController->GetBlackboard()->SetValueAsVector(BlackboardKey.SelectedKeyName,Location.Location);
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

FString UBTT_FindRandomLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
