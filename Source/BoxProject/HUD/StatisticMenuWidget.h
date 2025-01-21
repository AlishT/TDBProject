// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatisticMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UStatisticMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* MainMenu = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UButton* NextLevel = nullptr;

	UFUNCTION()
	void OnMenu();

	UFUNCTION()
	void OnNextLevel();

public:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* ElimEnemiesNum = nullptr;

	UPROPERTY(Meta =(BindWidget))
	class UTextBlock* EnemisNumber = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class  UTextBlock* BestLevelTime = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* CurrentLevelTime = nullptr;
};
