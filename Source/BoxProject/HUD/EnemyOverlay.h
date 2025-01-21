// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnOverlay.h"
#include "EnemyOverlay.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UEnemyOverlay : public UPawnOverlay
{
	GENERATED_BODY()
	
public:
	void SetEnemyHealthBar(float Health);
};
