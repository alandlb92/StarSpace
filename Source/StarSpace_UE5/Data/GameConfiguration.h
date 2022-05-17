#pragma once
#include "GameConfiguration.generated.h"

USTRUCT()
struct FGameConfiguration
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool MusicOn;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool SoundFXOn;

	FGameConfiguration()
	{
		MusicOn = true;
		SoundFXOn = true;
	}


	FGameConfiguration(FGameConfiguration* gameConfiguration)
	{
		MusicOn = gameConfiguration->MusicOn;
		SoundFXOn = gameConfiguration->SoundFXOn;
	}
};