// Fill out your copyright notice in the Description page of Project Settings.


#include "StatisticMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BoxProject/GameMode/BaseGameMode.h"

void UStatisticMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenu)
	{
		MainMenu->OnClicked.AddDynamic(this, &UStatisticMenuWidget::OnMenu);
	}

	if (NextLevel)
	{
		NextLevel->OnClicked.AddDynamic(this, &UStatisticMenuWidget::OnNextLevel);
	}

}

void UStatisticMenuWidget::OnMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

void UStatisticMenuWidget::OnNextLevel()
{
	ABaseGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseGameMode>();
	if (GameMode)
	{
		GameMode->OpenNextLevel();
	} 
}

