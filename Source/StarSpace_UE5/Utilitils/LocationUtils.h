// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STARSPACE_UE5_API LocationUtils
{
public:
	LocationUtils();
	~LocationUtils();
	static bool IsAppearingOnTheFirstPlayersScreen(FVector fVector, UWorld* world);
};
