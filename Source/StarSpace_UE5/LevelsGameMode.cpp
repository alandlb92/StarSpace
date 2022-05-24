// Fill out your copyright notice in the Description page of Project Settings.
#include "LevelsGameMode.h"

void ALevelsGameMode::AddOnLoadCallBack(function<void()> callBack)
{
	_loadCallBacksList.push_back(callBack);
}

void ALevelsGameMode::VerifyLoadingState()
{
	GetStarSpaceGameState();
	SetGameStateLoadCallBack();
}

AStarSpaceGameState* ALevelsGameMode::StarSpaceGameState()
{
	return _starSpaceGameState;
}

void ALevelsGameMode::GetStarSpaceGameState()
{
	_starSpaceGameState = GetGameState<AStarSpaceGameState>();
	if (!_starSpaceGameState)
	{
		UE_LOG(LogTemp, Error, TEXT("Game state not found"));
	}
}

void  ALevelsGameMode::SetGameStateLoadCallBack()
{
	if (_starSpaceGameState)
	{
		if (_starSpaceGameState->IsLoading)
			_starSpaceGameState->AddOnloadCallBack(bind(&ALevelsGameMode::OnLoadStateComplete, this));
		else
			OnLoadStateComplete();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game State Load Call Back not seted"));
	}
}


void ALevelsGameMode::OnLoadStateComplete()
{
	for (auto callBack : _loadCallBacksList)
	{
		callBack();
	}
}