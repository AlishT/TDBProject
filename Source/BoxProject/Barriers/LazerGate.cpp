// Fill out your copyright notice in the Description page of Project Settings.


#include "LazerGate.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/Components/GateMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "BoxProject/Barriers/LazerBarrier.h"

ALazerGate::ALazerGate()
{
	PrimaryActorTick.bCanEverTick = true;

	LeftGateMesh = CreateDefaultSubobject<UGateMeshComponent>(TEXT("LeftGateMesh"));
	LeftGateMesh->SetupAttachment(GetLazerCollision());
	
	RightGateMesh = CreateDefaultSubobject<UGateMeshComponent>(TEXT("RightGateMesh"));
	RightGateMesh->SetupAttachment(GetLazerCollision());

	LeftHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("LeftHealthBar"));
	LeftHealthBar->SetupAttachment(LeftGateMesh);
	
	RightHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("RightHealthBar"));
	RightHealthBar->SetupAttachment(RightGateMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetLazerCollision());
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALazerGate::OnWarningZone);
}

void ALazerGate::BeginPlay()
{
	Super::BeginPlay();

	LeftGateMesh->SetWidget(LeftHealthBar->GetWidget());

	RightGateMesh->SetWidget(RightHealthBar->GetWidget());

}

void ALazerGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LeftGateMesh->IsEliminated() && RightGateMesh->IsEliminated())
	{
		Destroy();
	}
}

void ALazerGate::LazerColorChenged()
{
	UMaterialInstanceDynamic* DynamicMaterial = GetLazerMesh()->CreateDynamicMaterialInstance(0);
	
	GetLazerMesh()->SetMaterial(0, DynamicMaterial);
	
	DynamicMaterial->SetVectorParameterValue(LazerParamName, LazerColor);
}

void ALazerGate::OnWarningZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor->IsA(PlayerClass))
	{
		LazerColorChenged();
	}
}

