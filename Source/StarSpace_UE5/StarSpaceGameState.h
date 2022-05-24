// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Data/GameConfiguration.h"
#include "Data/PlayerConfiguration.h"
#include "Save/SaveGameSlot.h"
#include <iostream>
#include <list>
#include "StarSpaceGameState.generated.h"
using namespace std;
/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API AStarSpaceGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	FGameConfiguration* GameConfig;
	FPlayerConfiguration* PlayerConfig;
	void SaveState();
	void AddOnloadCallBack(function<void()> callBack);

	bool IsLoading = true;

private:
	void LoadGameAsync();
	void OnLoadCompleted(const FString& SaveNameFile, const int32 UserIndex, USaveGame* LoadedGame);
	void SaveGameAsync();
	void OnSaveCompleted(const FString& SaveNameFile, const int32 UserIndex, bool success);
	
	void OnLoadCallBack();
	list<function<void()>> _loadCallBacksList;
};
