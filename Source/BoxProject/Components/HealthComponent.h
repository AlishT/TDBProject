// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class USoundCue;
class ABasePlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChenged, float, Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOXPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChenged OnHealthChenged;

protected:
	virtual void BeginPlay() override;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Default", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	USoundCue* HitSound = nullptr;

	UPROPERTY(Transient)
	ABasePlayerController* BasePC = nullptr;

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser);

public:
	void UpdatePlayerHealthHUD();
	
	void UpdateEnemyHealthHUD();

	void UpdateCurrentHealth();

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE void SetMaxHealth(const float Health) { MaxHealth = Health; }
};
