// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEnd.h"
#include "Components/BoxComponent.h"
#include "BoxProject/Controllers/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelEnd::ALevelEnd()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelEnd::OnBeginOverlap);

}

void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelEnd::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(PlayerClass))
	{
		ABasePlayerController* Controller = OtherActor->GetInstigatorController<ABasePlayerController>();

		if (!Controller) return;
		Controller->OpenEndLevelMenu();
	}
}

