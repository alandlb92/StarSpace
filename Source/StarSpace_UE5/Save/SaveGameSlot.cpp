// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSlot.h"
USaveGameSlot::USaveGameSlot()
{
	FileName = TEXT("starSpaceData");
}

void USaveGameSlot::SetGameConfiguration(FGameConfiguration GameConfig)
{
	_gameConfig = new FGameConfiguration(GameConfig);
}

void USaveGameSlot::SetPlayerConfiguration(FPlayerConfiguration PlayerConfig)
{
	_playerConfig = new FPlayerConfiguration(PlayerConfig);
}

FGameConfiguration USaveGameSlot::GetGameConfiguration()
{
	return _gameConfig;
}

FPlayerConfiguration USaveGameSlot::GetPlayerConfiguration()
{
	return _playerConfig;
}