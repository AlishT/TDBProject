// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PawnOverlay.generated.h"

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UPawnOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* HealthBar = nullptr;
};
