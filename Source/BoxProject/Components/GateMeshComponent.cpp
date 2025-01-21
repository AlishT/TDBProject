// Fill out your copyright notice in the Description page of Project Settings.


#include "GateMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "BoxProject/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "BoxProject/HUD/EnemyOverlay.h"

UGateMeshComponent::UGateMeshComponent()
{

}

void UGateMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	MeshHealth = MaxMeshHealth;

	UpdateHealthBar();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UGateMeshComponent::OnTakeDamage);
}

void UGateMeshComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	MeshHealth -= Damage;

	ElimHandler(MeshHealth);
}

void UGateMeshComponent::ElimHandler(float Health)
{
	UpdateHealthBar();

	if (Health > 0) return;

	SetVisibility(false);

	if (ElimPartical)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ElimPartical, GetComponentTransform());
	}

	if (ElimSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ElimSound, GetComponentLocation());
	}

	bEliminated = true;
}

void UGateMeshComponent::UpdateHealthBar()
{
	if (!Widget) return;

	UEnemyOverlay* GateOverlay = Cast<UEnemyOverlay>(Widget);

	if (GateOverlay)
	{
		float Health = MeshHealth / MaxMeshHealth;
		GateOverlay->SetEnemyHealthBar(Health);
	}
}
