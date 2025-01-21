// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ShootTarget.h"
#include "BoxProject/Controllers/EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BoxProject/Pawn/EnemyPawn.h"

EBTNodeResult::Type UBTT_ShootTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

	AEnemyController* AIController = Cast<AEnemyController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		AEnemyPawn* AIPawn = Cast<AEnemyPawn>(AIController->GetPawn());

		if (AIPawn && AIController->GetFocusActor())
		{
			FVector TargetLocation = AIController->GetFocusActor()->GetActorLocation();
			AIPawn->Shoot(TargetLocation);
		}
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
