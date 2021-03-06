// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/StreamableManager.h"
#include "../LoadingScreen/Public/LoadingScreen.h"
#include "StarSpace_UE5GameModeBase.generated.h"

/**
 *
 */

UCLASS()
class STARSPACE_UE5_API AStarSpace_UE5GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:	

protected:
	virtual void StartPlay() override;
};
