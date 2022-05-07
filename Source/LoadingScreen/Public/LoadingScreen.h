// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class ILoadingScreenModule : public IModuleInterface
{
public:
	static inline ILoadingScreenModule& Get()
	{
		return FModuleManager::LoadModuleChecked<ILoadingScreenModule>("LoadingScreen");
	}

	virtual void StartInGameLoadingScreen(bool bplayUntilStopped, float playTime) = 0;

	virtual void StopInGameLoadingScreen() = 0;
};