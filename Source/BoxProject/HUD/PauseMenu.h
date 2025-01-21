// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* Return = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UButton* Settings = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UButton* Quit = nullptr;

	UFUNCTION()
	void OnReturn();

	UFUNCTION()
	void OnSettings();

	UFUNCTION()
	void OnQuit();
};
