// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USoundCue;
class UAbilityComponent;
class UBoxGameInstance;
class UParticleSystem;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class BOXPROJECT_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()
	
public:
	APlayerPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "CameraBoom")
	USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerCamera")
	UCameraComponent* PlayerCamera = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AbilityComponent")
	UAbilityComponent* AbilityComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* MoveAction = nullptr;
	
	//UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	//class UInputAction* MoveRightAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* LookAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* FireAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	class UInputAction* PauseMenuAction = nullptr;

	UPROPERTY()
	float RotationSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	float AimDistance = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	UParticleSystem* TargetSystem = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	UNiagaraSystem* LevelUpSystem = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	USoundCue* LevelUpSound = nullptr;

	UPROPERTY()
	float CrosshairOffTime = 0.25f;

	UPROPERTY()
	float CurrentCrosshairTime = 0.f;

	float IncreaseProperty(float Prop, float Percent);

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void OpenPauseMenu();
	
	//UFUNCTION()
	//void MoveRight(const FInputActionValue& Value);

	void ShowCrosshair();

	bool WallCheced();

public:
	void IncreasePlayerStats(float Percent, UBoxGameInstance* GameInstance);

	void UpdatePlayerStats(UBoxGameInstance* GameInstance);

	void ShowLevelUpSystem();

	FORCEINLINE UAbilityComponent* GetAbilityComponent() const {return AbilityComponent;}
	FORCEINLINE void SetRotationSpeed(float RotateValue) { RotationSpeed = RotateValue; };
	
};
