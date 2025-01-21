// Fill out your copyright notice in the Description page of Project Settings.


#include "LazerBarrier.h"
#include "Components/BoxComponent.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/Components/AbilityComponent.h"

ALazerBarrier::ALazerBarrier()
{
	PrimaryActorTick.bCanEverTick = true;

	LazerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LazerCollision"));
	SetRootComponent(LazerCollision);
	LazerCollision->OnComponentBeginOverlap.AddDynamic(this, &ALazerBarrier::OnLazerOverlap);

	LazerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LazerMesh"));
	LazerMesh->SetupAttachment(LazerCollision);
}

void ALazerBarrier::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALazerBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;

	if (bLazerActive)
	{
		LazerMesh->SetVisibility(bLazerActive);

		if (CurrentTime >= LazerActiveTime)
		{
			bLazerActive = false;
			CurrentTime = 0.f;
		}
	}
	else 
	{
		LazerMesh->SetVisibility(bLazerActive);

		if (CurrentTime >= LazerDeactiveTime)
		{
			bLazerActive = true;
			CurrentTime = 0.f;
		}
	}
}

void ALazerBarrier::OnLazerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(PlayerClass) && bLazerActive)
	{
		APlayerPawn* Player = Cast<APlayerPawn>(OtherActor);

		if (Player && Player->GetAbilityComponent())
		{
			Player->GetAbilityComponent()->DeactivateShield();

			AController* OwnerInstigator = OtherActor->GetInstigatorController();
			UClass* DamageTypeClass = UDamageType::StaticClass();

			UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, DamageTypeClass);
		}
	}
}

