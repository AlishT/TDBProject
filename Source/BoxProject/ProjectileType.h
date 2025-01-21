#pragma once

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	EPT_DefaultBullet UMETA(DisplayName = "DefaultBullet"),
	EPT_ArmoredBullet UMETA(DisplayName = "ArmoredBullet"),
	EPT_TwoDefaultBullet UMETA(DisplayName = "TwoDefaultBullet"),
	EPT_TwoArmoredBullet UMETA(DisplayName = "TwoArmoredBullet"),
	EPT_ThreeDefaultBullets UMETA(DisplayName = "ThreeDefaultBullets"),
	EPT_ThreeArmoredBullets UMETA(DisplayName = "ThreeArmoredBullets"),
	EPT_SingleRocket UMETA(DisplayName = "SingleRocket"),
	EPT_TwoRockets UMETA(DisplayName = "TwoRockets"),
	EPT_ThreeRockets UMETA(DisplayName = "ThreeRockets"),
	EPT_Lazer UMETA(DisplayName = "Lazer"),
	EPT_TwoLazer UMETA(DisplayName = "TwoLazer"),
	EPT_ThreeLazer UMETA(DisplayName = "ThreeLazer"),

	EPT_MAX UMETA(DisplayName = "DefaultMAX")
};
