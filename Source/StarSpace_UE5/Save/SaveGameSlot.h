// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Data/GameConfiguration.h"
#include "../Data/PlayerConfiguration.h"
#include "SaveGameSlot.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API USaveGameSlot : public USaveGame
{
	GENERATED_BODY()
public:
	USaveGameSlot();

	FString FileName;

	void SetGameConfiguration(FGameConfiguration GameConfig);
	void SetPlayerConfiguration(FPlayerConfiguration PlayerConfig);

	FGameConfiguration GetGameConfiguration();
	FPlayerConfiguration GetPlayerConfiguration();

private:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FGameConfiguration _gameConfig;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FPlayerConfiguration _playerConfig;
};
