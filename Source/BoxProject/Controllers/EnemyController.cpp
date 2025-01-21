// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BoxProject/Pawn/EnemyPawn.h"
#include "BoxProject/GameMode/BaseGameMode.h"

AEnemyController::AEnemyController()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	check(BehaviorTreeComp);

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard "));
	check(BlackboardComp);

	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnTargetDetected);
	AIPerceptionComp->OnTargetPerceptionForgotten.AddDynamic(this, &AEnemyController::OnTargetForgotten);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn) return;

	AEnemyPawn* AIPawn = Cast<AEnemyPawn>(InPawn);

	if (AIPawn->GetBehaviorTree())
	{
		BlackboardComp->InitializeBlackboard(*(AIPawn->GetBehaviorTree()->BlackboardAsset));
		
		BehaviorTreeComp->StartTree(*(AIPawn->GetBehaviorTree()));
	}

	ABaseGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();
	
	if (GameMode)
	{
		GameMode->OnPlayerElim.AddDynamic(this, &AEnemyController::OnElim);
	}
}

void AEnemyController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->IsA(EnemyClass))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			SetFocus(Actor);
			FVector EnemyLocation = GetFocusActor()->GetActorLocation();

			BlackboardComp->SetValueAsObject(TEXT("Target"), GetFocusActor());
			BlackboardComp->SetValueAsBool(TEXT("bEnemyDetected"), true);
			Blackboard->SetValueAsVector(TEXT("TargetLocation"), EnemyLocation);
		}
	}
}

void AEnemyController::OnTargetForgotten(AActor* Actor)
{
	ClearFocus(EAIFocusPriority::LastFocusPriority);

	SetFocus(nullptr);
	BlackboardComp->SetValueAsBool(TEXT("bEnemyDetected"), false);
}

void AEnemyController::OnElim(bool bElim)
{
	if (bElim)
	{
		SetFocus(nullptr);
		//BlackboardComp->SetValueAsBool(TEXT("bEnemyDetected"), false);
	}
}
