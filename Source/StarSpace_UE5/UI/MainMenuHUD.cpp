// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"


void AMainMenuHUD::BeginPlay()
{
	if (_mainMenuWidgetClass)
	{
		_mainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), _mainMenuWidgetClass);
		if (_mainMenuWidget != nullptr)
		{
			_mainMenuWidget->AddToViewport();
		}
	}
}