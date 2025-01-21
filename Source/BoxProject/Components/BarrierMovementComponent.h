#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BarrierMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOXPROJECT_API UBarrierMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UBarrierMovementComponent();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Default")
	FVector MovingDirection = FVector::ZeroVector;

	UPROPERTY()
	FVector StartLocation = FVector::ZeroVector;

	UPROPERTY()
	FVector EndLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Default")
	float Distance = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float CurrentTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float TimeToMove = 0.f;

	UPROPERTY()
	float Progress = 0.f;

	UPROPERTY(EditAnywhere, Category = "Default")
	float Speed = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
	float Direction = 1.f;

	UPROPERTY(EditAnywhere, Category = "Default")
	bool bMovable = false;

	UPROPERTY(Transient)
	AActor* CachedOwner = nullptr;

	void StartMoving();

	FVector GetNewPosition();
};
