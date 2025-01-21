// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ElimMenu.h"
#include "EndLevelMenu.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UEndLevelMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* RestartLevel = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UButton* NextLevel = nullptr;

	UFUNCTION()
	void OnNextLevel();

	UFUNCTION()
	void OnRestart();
};
