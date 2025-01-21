#include "BarrierMovementComponent.h"


UBarrierMovementComponent::UBarrierMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBarrierMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	CachedOwner = GetOwner();
}

void UBarrierMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bMovable) return;

	CurrentTime += DeltaTime;

	Progress = FMath::Clamp(CurrentTime / TimeToMove, 0.f, 1.f);

	if (CurrentTime >= TimeToMove)
	{
		CurrentTime = 0.f;

		Direction *= -1;

		StartMoving();

		return;
	}

	CachedOwner->SetActorLocation(GetNewPosition(), false, nullptr);
}

void UBarrierMovementComponent::StartMoving()
{
	StartLocation = CachedOwner->GetActorLocation();

	EndLocation = StartLocation + MovingDirection.GetSafeNormal() * Distance * Direction;

	TimeToMove = Distance / Speed;
}

FVector UBarrierMovementComponent::GetNewPosition()
{
	return FMath::InterpEaseInOut(StartLocation, EndLocation, Progress, 3.f);
}

