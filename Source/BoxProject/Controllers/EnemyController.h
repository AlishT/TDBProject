// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAIPerceptionComponent;
class AEnemyPawn;

/**
 * 
 */
UCLASS()
class BOXPROJECT_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController();

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviorTreeComp = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackboardComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AIPerceptionComp")
	UAIPerceptionComponent* AIPerceptionComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyClass")
	TSubclassOf<AActor> EnemyClass;

	//UPROPERTY(Transient)
	//AEnemyPawn* AIPawn = nullptr;

protected:
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetForgotten(AActor* Actor);

	UFUNCTION()
	void OnElim(bool bElim);

public:
	FORCEINLINE UBlackboardComponent* GetBlackboard() const {return Blackboard;}
};
