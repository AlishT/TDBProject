// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "BoxProject/GameMode/BaseGameMode.h"
#include "BoxProject/Controllers/BasePlayerController.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBeginOverlap);

	CheckpointTransform = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CheckpointTransform"));
	CheckpointTransform->SetupAttachment(CollisionBox);

}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bActivate) return;

	if (OtherActor->IsA(PlayerClass))
	{
		ABaseGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();

		ABasePlayerController* PlayerController = OtherActor->GetInstigatorController<ABasePlayerController>();

		if (GameMode && PlayerController)
		{
			FTransform SpawnLocation = CheckpointTransform->GetComponentTransform();
			FRotator PawnRotation = OtherActor->GetActorRotation();

			GameMode->SetSpawnLocation(SpawnLocation);
			GameMode->SetPawnRotation(PawnRotation);

			PlayerController->SetCheckpointTextVisible(ESlateVisibility::Visible);

			bActivate = true;
		}
	}
}

