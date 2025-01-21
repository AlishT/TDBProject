// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Options.generated.h"

class UBoxGameInstance;

/**
 * 
 */
UCLASS()
class BOXPROJECT_API UOptions : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UButton* Back = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class USlider* RotateSlider = nullptr;

	UPROPERTY(Meta = (BindWidget))
	class USlider* MusicSlider = nullptr;

	UFUNCTION()
	void OnBack();

	UFUNCTION()
	void OnRatateValueChanged(float Value);

	UFUNCTION()
	void OnMusicValueChanged(float Value);

protected:
	UPROPERTY(BlueprintReadOnly)
	UBoxGameInstance* BoxGameInstance = nullptr;
};
