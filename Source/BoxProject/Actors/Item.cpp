// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/BoxComponent.h"
#include "BoxProject/Pawn/BasePawn.h"
#include "BoxProject/Components/CombatComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(CollisionBox);
	ItemMesh->GetCollisionResponseToChannel(ECollisionChannel::ECC_OverlapAll_Deprecated);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (ItemSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(ItemSystem, GetRootComponent(), FName(), GetActorLocation(), GetActorRotation(), EAttachLocation::KeepWorldPosition, false);
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bRotatedMesh) return;

	NewRotateValue += RotateValue;

	ItemMesh->SetWorldRotation(FRotator(0.f, NewRotateValue, 0.f));
}

void AItem::PlayPickUpSound()
{
	if (!PickUpSound) return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickUpSound, GetActorLocation());
}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor && !OtherActor->IsA(APlayerPawn::StaticClass())) return;

}


