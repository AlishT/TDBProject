// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnOverlay.h"
#include "PlayerOverlay.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UPlayerOverlay : public UPawnOverlay
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* CkeckpointText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* LivesCountText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* LevelCountText = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* ExpBar = nullptr;

	virtual void NativeConstruct() override;
private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* Pause = nullptr;

	UFUNCTION()
	void OnPause();
};
