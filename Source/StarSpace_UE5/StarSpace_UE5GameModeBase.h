// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/AnimationUtils/UIAnimationUtils.h"
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

protected:
	virtual void StartPlay() override;
	virtual void Logout(AController* Exiting) override;

private:
	UIAnimationUtils* _UIAnimationUtils;
};
