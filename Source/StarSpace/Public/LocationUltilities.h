// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

/**
 * 
 */
class STARSPACE_API LocationUltilities
{
public:
	LocationUltilities();
	~LocationUltilities();
	static bool IsAppearingOnTheFirstPlayersScreen(FVector fVector, UWorld* world);
};
