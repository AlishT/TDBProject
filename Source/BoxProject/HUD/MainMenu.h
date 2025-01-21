// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UBoxGameInstance;

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* Resume = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	class UButton* NewGame = nullptr;

	UPROPERTY(Meta =(BindWidget))
	class UButton* Settings = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UButton* QuitGame = nullptr;

	UPROPERTY(Transient)
	UBoxGameInstance* GameInstance = nullptr;

	UFUNCTION()
	void OnResume();

	UFUNCTION()
	void OnNewGame();

	UFUNCTION()
	void OnSettings();

	UFUNCTION()
	void OnQuitGame();
};
