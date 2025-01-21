// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatedBarrier.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "BoxProject/Components/AbilityComponent.h"
#include "BoxProject/Barriers/LazerBarrier.h"
#include "BoxProject/Components/BarrierMovementComponent.h"
#include "Sound/SoundCue.h"
#include "Components/StaticMeshComponent.h"

ARotatedBarrier::ARotatedBarrier()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMesh);

	LazerRotatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LazerRotatorMesh"));
	LazerRotatorMesh->SetupAttachment(BaseMesh);

	BarrierMovement = CreateDefaultSubobject<UBarrierMovementComponent>(TEXT("BarrierMovement"));

	GetLazerMesh()->SetupAttachment(LazerRotatorMesh);
	GetLazerCollision()->SetupAttachment(GetLazerMesh());
}

void ARotatedBarrier::BeginPlay()
{
	Super::BeginPlay();
	
	if (!LazerSound) return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LazerSound, GetActorLocation());
}

void ARotatedBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateLazer();
}

void ARotatedBarrier::RotateLazer()
{
	FRotator StartRotation = LazerRotatorMesh->GetComponentRotation();

	float RotateDirection = (bRotateRight) ? StartRotation.Yaw + Direction : StartRotation.Yaw - Direction;

	FRotator Rotation = FRotator(0.f, RotateDirection, 0.f);
	
	FRotator EndRotation = FMath::RInterpConstantTo(StartRotation, Rotation, 0.2f, RotateSpeed);

	LazerRotatorMesh->SetWorldRotation(EndRotation);
}

