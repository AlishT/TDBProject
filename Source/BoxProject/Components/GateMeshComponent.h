// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GateMeshComponent.generated.h"

class UWidgetComponent;
class UHealthComponent;
class UParticleSystem;
class USoundCue;
class UUserWidget;
/**
 * 
 */
UCLASS()
class BOXPROJECT_API UGateMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UGateMeshComponent();

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(Transient)
	UUserWidget* Widget = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ElimPartical = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* ElimSound = nullptr;

	UPROPERTY()
	bool bEliminated = false;

	UPROPERTY()
	float MeshHealth = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float MaxMeshHealth = 0.f;

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser);

	UFUNCTION()
	void ElimHandler(float Health);

	void UpdateHealthBar();

public:
	FORCEINLINE bool IsEliminated() const { return bEliminated; }
	FORCEINLINE void SetWidget(UUserWidget* MeshWidget) { Widget = MeshWidget; }
};
