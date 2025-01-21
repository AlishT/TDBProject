// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "BoxProject/Projectile/Projectile.h"
#include "BoxProject/Pawn/BasePawn.h"
#include "GameFramework/FloatingPawnMovement.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	StartSheildTimer(DeltaTime);
	StartEnergyTimer(DeltaTime);
}

void UAbilityComponent::StartSheildTimer(float DeltaTime)
{
	if (!bShieldActivate) return;
	
	CurrentShieldTime += DeltaTime;

	if (CurrentShieldTime >= ShieldTime)
	{
		DeactivateShield();
	}
}

void UAbilityComponent::StartEnergyTimer(float DeltaTime)
{
	if (!bEnergyActivate) return;
	
	CurrentEnergyTime += DeltaTime;

	if (CurrentEnergyTime >= EnergyTime)
	{
		DeactivateEnergy();
	}
	
}

void UAbilityComponent::ActivateShield()
{
	bShieldActivate = true;
	CurrentShieldTime = 0.f;

	if (ShieldSystem && bShieldActivate)
	{
		ShieldSystemComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(ShieldSystem, GetOwner()->GetRootComponent(), FName(), GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), EAttachLocation::KeepWorldPosition, false);
	}
}

void UAbilityComponent::DeactivateShield()
{
	if (ShieldSystemComponent)
	{
		ShieldSystemComponent->DestroyInstance();
	}

	bShieldActivate = false;
}

void UAbilityComponent::ActivateEnergy()
{
	bEnergyActivate = true;
	CurrentEnergyTime = 0;

	if (bEnergyActivate && EnergySystem)
	{
		EnergySystemComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(EnergySystem, GetOwner()->GetRootComponent(), FName(), GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), EAttachLocation::KeepWorldPosition, false);
	}

	ABasePawn* Player = GetOwner<ABasePawn>();

	if (Player && Player->GetPawnMovement() && EnergyPercent != 0.f)
	{
		DefaultSpeed = Player->GetPawnMovement()->MaxSpeed;
		Player->GetPawnMovement()->MaxSpeed += DefaultSpeed * EnergyPercent / 100;
	}
}

void UAbilityComponent::DeactivateEnergy()
{
	ABasePawn* Player = GetOwner<ABasePawn>();

	if (Player && Player->GetPawnMovement())
	{
		Player->GetPawnMovement()->MaxSpeed = DefaultSpeed;
	}

	if (EnergySystemComponent)
	{
		EnergySystemComponent->DestroyInstance();
	}

	bEnergyActivate = false;
}
