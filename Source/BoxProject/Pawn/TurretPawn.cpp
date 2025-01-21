// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Components/CapsuleComponent.h"
#include "BoxProject/Components/CombatComponent.h"

ATurretPawn::ATurretPawn()
{
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(GetCapsuleComponent());
}

void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretPawn::RotateToTarget(FVector& TargetLocation)
{
	FVector StartLocation = GetBaseMesh()->GetComponentLocation();
	FRotator StartRotation = GetBaseMesh()->GetComponentRotation();

	FVector TurretDirection = TargetLocation - StartLocation;
	TurretDirection.Z = 0.f;

	FRotator Rotation = TurretDirection.Rotation();
	Rotation.Normalize();

	FRotator TurretRotation = FMath::RInterpConstantTo(StartRotation, Rotation, 0.5f, GetInterpRotateSpeed());

	GetBaseMesh()->SetWorldRotation(TurretRotation);
}

void ATurretPawn::Shoot(FVector& TargetLocation)
{
	FVector CurrentDirection = GetBaseMesh()->GetForwardVector();
	FVector TargetDirection = TargetLocation - GetBaseMesh()->GetComponentLocation();

	float RotationAngleCosine = CurrentDirection.CosineAngle2D(TargetDirection);
	float RotationAngle = FMath::RadiansToDegrees(FMath::Acos(RotationAngleCosine));

	if (RotationAngle <= GetTurretAimError() && GetCombat())
	{
		GetCombat()->Shoot();
	}
}

void ATurretPawn::RotateTurret()
{
	CurrentRotateValue += RotateValue;

	GetBaseMesh()->SetWorldRotation(FRotator(0.f, CurrentRotateValue, 0.f));
}
