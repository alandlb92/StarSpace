#pragma once

#include "PlayerConfiguration.generated.h"

USTRUCT()
struct FPlayerConfiguration
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool FowardCannon;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool AngleCannon;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool SideCannon;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int Speed;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int MaxHeating;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int BulletLevel;

	FPlayerConfiguration()
	{
		FowardCannon = false;
		AngleCannon = false;
		SideCannon = false;
		Speed = 1;
		MaxHeating = 1;
		BulletLevel = 1;
	}

	FPlayerConfiguration(FPlayerConfiguration* playerConfiguration)
	{
		FowardCannon = playerConfiguration->FowardCannon;
		AngleCannon = playerConfiguration->AngleCannon;
		SideCannon = playerConfiguration->SideCannon;
		Speed = playerConfiguration->Speed;
		MaxHeating = playerConfiguration->MaxHeating;
		BulletLevel = playerConfiguration->BulletLevel;
	}
};