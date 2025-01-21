// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_TurretPatrol.h"
#include "BoxProject/Controllers/EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BoxProject/Pawn/TurretPawn.h"

EBTNodeResult::Type UBTT_TurretPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

	AEnemyController* AIController = Cast<AEnemyController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		ATurretPawn* AIPawn = Cast<ATurretPawn>(AIController->GetPawn());

		if (AIPawn)
		{
			AIPawn->RotateTurret();
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
