// Fill out your copyright notice in the Description page of Project Settings.


#include "UIAnimationUtils.h"

UIAnimationUtils::UIAnimationUtils()
{
	_colorAnimationUI = new ColorAnimationUI();
	_colorAnimationUI->Initialize();

	_tickDelegate = FTickerDelegate::CreateRaw(this, &UIAnimationUtils::Tick);
	_tickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(_tickDelegate);

}

void UIAnimationUtils::LogOut()
{
	FTSTicker::GetCoreTicker().RemoveTicker(_tickDelegateHandle);
	_colorAnimationUI->LogOut();
	delete _colorAnimationUI;
	_colorAnimationUI = NULL;
}

bool UIAnimationUtils::Tick(float DeltaTime)
{
	_colorAnimationUI->Tick(DeltaTime);
	return true;
}