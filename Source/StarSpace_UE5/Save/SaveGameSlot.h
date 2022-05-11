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

	void SetGameConfiguration(GameConfiguration GameConfig);
	void SetPlayerConfiguration(PlayerConfiguration PlayerConfig);

	GameConfiguration GetGameConfiguration();
	PlayerConfiguration GetPlayerConfiguration();

private:
	GameConfiguration _gameConfig;
	PlayerConfiguration _playerConfig;
};
