// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "BoxProject/Controllers/BasePlayerController.h"
#include "BoxProject/Pawn/EnemyPawn.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "BoxProject/Pawn/PlayerPawn.h"
#include "BoxProject/Components/AbilityComponent.h"
#include "BoxProject/GameInstance/BoxGameInstance.h"
#include "BoxProject/Saves/Saves.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);

	CurrentHealth = MaxHealth;

	UpdatePlayerHealthHUD();
	UpdateEnemyHealthHUD();
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	APlayerPawn* Player = GetOwner<APlayerPawn>();
	
	bool bShield = Player && Player->GetAbilityComponent() && Player->GetAbilityComponent()->CheckShieldActivation();

	if (bShield) return;
	
	CurrentHealth -= Damage;
	
	UpdatePlayerHealthHUD();
	UpdateEnemyHealthHUD();

	if (HitSound && DamageCauser)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, DamageCauser->GetActorLocation());
	}

	OnHealthChenged.Broadcast(CurrentHealth);
}

void UHealthComponent::UpdatePlayerHealthHUD()
{
	APawn* Pawn = GetOwner<APawn>();

	if (Pawn)
	{
		BasePC = Pawn->GetController<ABasePlayerController>();

		if (!BasePC) return;

		BasePC->SetHealthHUD(MaxHealth, CurrentHealth);
	}
}

void UHealthComponent::UpdateEnemyHealthHUD()
{
	AEnemyPawn* EnemyPawn = GetOwner<AEnemyPawn>();

	if (!EnemyPawn) return;

	EnemyPawn->SetEnemyProgressBar(CurrentHealth, MaxHealth);
}

void UHealthComponent::UpdateCurrentHealth()
{
	CurrentHealth = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("MaxHealth: %f"), MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("CurrentHealth: %f"), CurrentHealth);
	
	UpdatePlayerHealthHUD();
}

