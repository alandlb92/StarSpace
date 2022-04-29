// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIAnimationBase.h"
#include "ColorAnimationUI.h"

class STARSPACE_UE5_API UIAnimationUtils
{
public:
	UIAnimationUtils();
	bool Tick(float DeltaTime);
	ColorAnimationUI* GetColorAnimationUI() { return _colorAnimationUI; }
	void LogOut();


private:
	ColorAnimationUI* _colorAnimationUI;
	FTickerDelegate _tickDelegate;
	FTSTicker::FDelegateHandle _tickDelegateHandle;
};
