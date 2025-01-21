// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class USphereComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOXPROJECT_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilityComponent();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "NiagaraSystem")
	UNiagaraSystem* ShieldSystem = nullptr;

	UPROPERTY(Transient)
	UNiagaraComponent* ShieldSystemComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "NiagaraSystem")
	UNiagaraSystem* EnergySystem = nullptr;

	UPROPERTY(Transient)
	UNiagaraComponent* EnergySystemComponent = nullptr;

	UPROPERTY()
	bool bShieldActivate = false;

	UPROPERTY()
	float CurrentShieldTime = 0.f;

	UPROPERTY()
	float ShieldTime = 15.f;

	UPROPERTY()
	bool bEnergyActivate = false;

	UPROPERTY()
	float CurrentEnergyTime = 0.f;

	UPROPERTY()
	float EnergyTime = 15.f;

	UPROPERTY()
	float EnergyPercent = 50.f;

	UPROPERTY()
	float DefaultSpeed = 0.f;

	void StartSheildTimer(float DeltaTime);

	void StartEnergyTimer(float DeltaTime);

public:
	void ActivateShield();

	void DeactivateShield();

	void ActivateEnergy();

	void DeactivateEnergy();

	FORCEINLINE bool CheckShieldActivation() const { return bShieldActivate; }
	FORCEINLINE bool CheckEnergyActivation() const { return bEnergyActivate; }
	FORCEINLINE float GetShieldTime() const { return ShieldTime; }
	FORCEINLINE void SetShieldTime(const float Time) { ShieldTime = Time; }
	FORCEINLINE float GetEnergyTime() const { return EnergyTime; }
	FORCEINLINE void SetEnergyTime(const float Time) { EnergyTime = Time; }
};