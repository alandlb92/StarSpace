// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STARSPACE_UE5_API LocationUtils
{
public:
	static bool IsAppearingOnTheFirstPlayersScreen(FVector fVector, UWorld* world);
	static FVector2D GetFirstPlayersScreenSize(UWorld* world);
	static FVector2D CovertWorldLocationToFirstPlayersScreenLocation(FVector fVector, UWorld* world);
	static FVector GetRightTopFirstPlayerScreenWorldposition(UWorld* world);
	static FVector GetLeftBottonFirstPlayerScreenWorldposition(UWorld* world);
};
