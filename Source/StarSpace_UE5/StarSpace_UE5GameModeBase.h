// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/AnimationUtils/UIAnimationUtils.h"
#include "Engine/StreamableManager.h"
#include "../LoadingScreen/Public/LoadingScreen.h"
#include "Data/GameConfiguration.h"
#include "Data/PlayerConfiguration.h"
#include "Save/SaveGameSlot.h"
#include "StarSpace_UE5GameModeBase.generated.h"

/**
 *
 */

UCLASS()
class STARSPACE_UE5_API AStarSpace_UE5GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:	
	UIAnimationUtils* GetUIAnimationUtils() { return _UIAnimationUtils; }
	GameConfiguration* GameConfig;
	PlayerConfiguration* PlayerConfig;

	bool IsLoadingOrSaveData;

protected:
	virtual void StartPlay() override;
	virtual void Logout(AController* Exiting) override;

private:
	UIAnimationUtils* _UIAnimationUtils;

	void LoadGameAsync();
	void OnLoadCompleted(const FString& SaveNameFile, const int32 UserIndex, USaveGame* LoadedGame);

	void SaveGameAsync();
	void OnSaveCompleted(const FString& SaveNameFile, const int32 UserIndex, bool success);



};
