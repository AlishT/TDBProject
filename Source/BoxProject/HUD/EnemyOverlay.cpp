// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyOverlay.h"
#include "Components/ProgressBar.h"

void UEnemyOverlay::SetEnemyHealthBar(float Health)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Health);
	}
}
