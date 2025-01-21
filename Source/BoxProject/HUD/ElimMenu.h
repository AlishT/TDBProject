// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ElimMenu.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UElimMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* MainMenu = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class UButton* RestartLevel = nullptr;

	UFUNCTION()
	void OnMenu();

	UFUNCTION()
	void OnRestart();
};
