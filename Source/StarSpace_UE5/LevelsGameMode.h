// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <list>
#include <iostream>
#include "GameFramework/GameModeBase.h"
#include "StarSpaceGameState.h"
#include "LevelsGameMode.generated.h"

using namespace std;

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API ALevelsGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void VerifyLoadingState();
	void AddOnLoadCallBack(function<void()> callBack);
	AStarSpaceGameState* StarSpaceGameState();

private:
	list<function<void()>> _loadCallBacksList;
	AStarSpaceGameState* _starSpaceGameState;
	void GetStarSpaceGameState();
	void GetPlayerSpaceship();
	void SetGameStateLoadCallBack();
	void OnLoadStateComplete();

};
