// Fill out your copyright notice in the Description page of Project Settings.


#include "LocationUtils.h"

bool LocationUtils::IsAppearingOnTheFirstPlayersScreen(FVector fVector, UWorld* world)
{
	FVector2D ScreenLocation = CovertWorldLocationToFirstPlayersScreenLocation(fVector, world);
	FVector2D screenSize = GetFirstPlayersScreenSize(world);

	if (ScreenLocation.X < 0 || ScreenLocation.Y < 0 || ScreenLocation.X > screenSize.X || ScreenLocation.Y > screenSize.Y)
		return false;
	else
		return true;
}

FVector2D LocationUtils::GetFirstPlayersScreenSize(UWorld* world)
{
	int32 ScreenSizeX;
	int32 ScreenSizeY;
	world->GetFirstPlayerController()->GetViewportSize(ScreenSizeX, ScreenSizeY);
	return FVector2D(ScreenSizeX, ScreenSizeY);
}

FVector2D LocationUtils::CovertWorldLocationToFirstPlayersScreenLocation(FVector fVector, UWorld* world)
{
	FVector2D ScreenLocation;
	world->GetFirstPlayerController()->ProjectWorldLocationToScreen(fVector, ScreenLocation);
	return ScreenLocation;
}

FVector LocationUtils::GetRightTopFirstPlayerScreenWorldposition(UWorld* world)
{
	FVector2D screenSize = GetFirstPlayersScreenSize(world);
	FVector WorldLocation;
	FVector WorldDirection;
	world->GetFirstPlayerController()->DeprojectScreenPositionToWorld(0, 0, WorldLocation, WorldDirection);
	return WorldLocation;
}

FVector LocationUtils::GetLeftBottonFirstPlayerScreenWorldposition(UWorld* world)
{
	FVector2D screenSize = GetFirstPlayersScreenSize(world);
	FVector WorldLocation;
	FVector WorldDirection;
	world->GetFirstPlayerController()->DeprojectScreenPositionToWorld(screenSize.X, screenSize.Y, WorldLocation, WorldDirection);
	return WorldLocation;
}