// Fill out your copyright notice in the Description page of Project Settings.


#include "LocationUtils.h"


LocationUtils::LocationUtils()
{
}

LocationUtils::~LocationUtils()
{
}


bool LocationUtils::IsAppearingOnTheFirstPlayersScreen(FVector fVector, UWorld* world)
{
	FVector2D ScreenLocation;
	world->GetFirstPlayerController()->ProjectWorldLocationToScreen(fVector, ScreenLocation);

	int32 ScreenSizeX;
	int32 ScreenSizeY;

	world->GetFirstPlayerController()->GetViewportSize(ScreenSizeX, ScreenSizeY);

	if (ScreenLocation.X < 0 || ScreenLocation.Y < 0 || ScreenLocation.X > ScreenSizeX || ScreenLocation.Y > ScreenSizeY)
		return false;
	else
		return true;
}