// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class UPlayerOverlay;

/**
 * 
 */
UCLASS()
class BOXPROJECT_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	UPROPERTY(EditDefaultsOnly, Category = "Player Stats")
	TSubclassOf<class UUserWidget> PlayerOverlayClass;

	UPROPERTY(Transient)
	UPlayerOverlay* PawnOverlay = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	void AddPlayerOverlay();
};
