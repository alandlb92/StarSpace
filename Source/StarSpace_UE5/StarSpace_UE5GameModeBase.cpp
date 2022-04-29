// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarSpace_UE5GameModeBase.h"
void AStarSpace_UE5GameModeBase::StartPlay()
{
	//Callet before alls begin play
	Super::StartPlay();
	_UIAnimationUtils = new UIAnimationUtils();
}

void AStarSpace_UE5GameModeBase::Logout(AController* Exiting)
{
	UE_LOG(LogTemp, Warning, TEXT("EXTING"));
	_UIAnimationUtils->LogOut();
	delete _UIAnimationUtils;
	_UIAnimationUtils = NULL;
}

