// Fill out your copyright notice in the Description page of Project Settings.


#include "GareDoor.h"
#include "Components/BoxComponent.h"
#include "BoxProject/Pawn/EnemyPawn.h"

AGareDoor::AGareDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SetRootComponent(DoorMesh);

	DoorTriger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door"));
	DoorTriger->SetupAttachment(DoorMesh);
}

void AGareDoor::BeginPlay()
{
	Super::BeginPlay();

	DoorTriger->OnComponentBeginOverlap.AddDynamic(this, &AGareDoor::OnOverlapBegin);

	EnemyCount = EnemyPawns.Num();

	OpenDoor();
}

void AGareDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bDoorActivate) return;

	if(EnemiesChecked())
	{
		CurrentTime += DeltaTime;

		Progress = FMath::Clamp(CurrentTime / OpenDoorTime, 0.f, 1.f);

		if(CurrentTime >= OpenDoorTime)
		{
			UE_LOG(LogTemp, Warning, TEXT("Door Deactivate"));
			bDoorActivate = false;
		}

		DoorMesh->SetWorldLocation(MovengDoor());
	}
}

bool AGareDoor::EnemiesChecked()
{
	for (AEnemyPawn* Enemy : EnemyPawns)
	{
		if (Enemy && Enemy->IsElimPawn() && !Enemy->IsLostDoorKey())
		{
			EnemyCount--;
			Enemy->SetLostDoorKey(Enemy->IsElimPawn());
			UE_LOG(LogTemp, Warning, TEXT("Enemy Destroy"));
			UE_LOG(LogTemp, Warning, TEXT("EnemyCount %i"), EnemyCount);
		}

		if (EnemyCount <= 0)
		{
			return true;
		}
	}

	return false;
}

void AGareDoor::OpenDoor()
{
	OpenDoorTime = Distance / Speed;

	StarLocation = DoorMesh->GetComponentLocation();

	EndLocation = StarLocation + MovingDirection.GetSafeNormal() * Distance;
}

FVector AGareDoor::MovengDoor()
{
	return FMath::InterpEaseIn(StarLocation, EndLocation, Progress, 0.3f);
}

void AGareDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(PlayerClass))
	{
		if (bTrigerActivate) return;
		UE_LOG(LogTemp, Warning, TEXT("EnemyCount %i"), EnemyCount);
		bDoorActivate = true;
		bTrigerActivate = true;
		UE_LOG(LogTemp, Warning, TEXT("Door Activate"));
	}
}

