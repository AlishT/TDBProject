// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "GameFramework/FloatingPawnMovement.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PartalMesh"));
	SetRootComponent(PortalMesh);

	PortalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollision"));
	PortalCollision->SetupAttachment(PortalMesh);
	PortalCollision->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnBeginOverlap);
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	WorldTargetPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), PoltalTargetPoint);
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if(OtherActor->IsA(PlayerClass))
	{ 
		//APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);
		
		//if (!Player) return;

		//Player->GetPawnMovement()->Velocity = FVector(0.f, 0.f, 0.f);
		//Player->SetActorLocation(WorldTargetPoint);
		OtherActor->SetActorLocation(WorldTargetPoint);
	}
}

