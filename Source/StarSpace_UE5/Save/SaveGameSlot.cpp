// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSlot.h"
USaveGameSlot::USaveGameSlot()
{
	FileName = TEXT("starSpaceData");
}

void USaveGameSlot::SetGameConfiguration(GameConfiguration GameConfig)
{
	_gameConfig = GameConfig;
}

void USaveGameSlot::SetPlayerConfiguration(PlayerConfiguration PlayerConfig)
{
	_playerConfig = PlayerConfig;
}

GameConfiguration USaveGameSlot::GetGameConfiguration()
{
	return _gameConfig;
}

PlayerConfiguration USaveGameSlot::GetPlayerConfiguration()
{
	return _playerConfig;
}