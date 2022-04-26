// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerSpaceshipState.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API APlayerSpaceshipState : public APlayerState
{
	GENERATED_BODY()
public:
	bool SideCannon;
	bool AngleCannon;
	bool FowardCannon;
	int Velocity;	
};
