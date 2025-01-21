// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainMenuGM.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API AMainMenuGM : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
