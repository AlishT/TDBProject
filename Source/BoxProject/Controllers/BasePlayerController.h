// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/SlateWrapperTypes.h"
#include "BasePlayerController.generated.h"

class ABaseHUD;
class UEnhancedInputLocalPlayerSubsystem;
class UUsetWidget;
/**
 * 
 */
UCLASS()
class BOXPROJECT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "InputMappingContex")
	class UInputMappingContext* MovingMC = nullptr;

	UPROPERTY(Transient)
	UEnhancedInputLocalPlayerSubsystem* Subsystem = nullptr;

	UPROPERTY(Transient)
	ABaseHUD* BaseHUD = nullptr;

	UPROPERTY()
	ESlateVisibility TextVisibility = ESlateVisibility::Hidden;

	UPROPERTY()
	float CurrentTextVisibilityTime = 0.f;

	UPROPERTY()
	float TextVisibilityTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> EndLevelMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> ElimMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> LoadingMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> StatisticMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly, Category ="Widgets")
	TSubclassOf<UUserWidget> SettingsMenuClass;

	void OpenMenu(TSubclassOf<UUserWidget> MenuClass, bool bShowMouse);

public:
	UPROPERTY()
	bool bMainMenu = true;

	UPROPERTY()
	bool bPauseMenu = false;

	virtual void Tick(float DeltaTime) override;

	void SetHealthHUD(float MaxHealth, float CurrentHealth);

	void SetExpHUD(float MaxExp, float Exp);

	void SetPlayerStatsHUD(int32 PlayerLevel, int32 PlayerLives);

	void SetCheckpointTextVisible(ESlateVisibility Type);

	void OpenMainMenu();

	void OpenEndLevelMenu();

	void OpenElimMenu();

	void OpenLoadingMenu();

	void OpenStatisticMenu(float CurrentTime, float BestTime, int32 ElinEnemies, int32 Eneimes);

	void OpenPauseMenu();

	void OpenSettingnsMenu();

	void AddMoving();
};
