// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_RotateToTarget.h"
#include "BoxProject/Controllers/EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BoxProject/Pawn/EnemyPawn.h"

EBTNodeResult::Type UBTT_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

	AEnemyController* AIConrtoler = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	
	if (AIConrtoler)
	{
		AEnemyPawn* AIPawn = Cast<AEnemyPawn>(AIConrtoler->GetPawn());

		if (AIPawn)
		{
			if(!AIConrtoler->GetFocusActor()) return EBTNodeResult::Failed;
			
			FVector Location = AIConrtoler->GetFocusActor()->GetActorLocation();
			AIPawn->RotateToTarget(Location);
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
