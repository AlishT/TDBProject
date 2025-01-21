// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "BoxProject/Components/CombatComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "BoxProject/HUD/EnemyOverlay.h"
#include "BoxProject/Components/HealthComponent.h"

AEnemyPawn::AEnemyPawn()
{
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBar->SetupAttachment(GetCapsuleComponent());
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (GetHealthComponent())
	{
		ElimExp = GetHealthComponent()->GetMaxHealth();
	}
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyPawn::SetEnemyProgressBar(float CurrentHealth, float MaxHealth)
{
	UEnemyOverlay* EnemyOverlay = Cast<UEnemyOverlay>(HealthBar->GetWidget());

	if (EnemyOverlay)
	{
		float Health = CurrentHealth / MaxHealth;
		EnemyOverlay->SetEnemyHealthBar(Health);
	}
}

void AEnemyPawn::RotateToTarget(FVector& TargetLocation)
{
	FVector StartLocation = GetActorLocation();
	FRotator StartRotation = GetActorRotation();

	FVector TurretDirection = TargetLocation - StartLocation;
	TurretDirection.Z = 0.f;

	FRotator Rotation = TurretDirection.Rotation();
	Rotation.Normalize();

	FRotator TurretRotation = FMath::RInterpConstantTo(StartRotation, Rotation, 0.2f, GetInterpRotateSpeed());

	SetActorRotation(TurretRotation);
}

void AEnemyPawn::Shoot(FVector& TargetLocation)
{
	if (GetCombat())
	{
		GetCombat()->Shoot();
	}
}

