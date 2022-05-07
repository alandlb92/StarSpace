// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"


void AMainMenuHUD::BeginPlay()
{
	if (_mainMenuWidgetClass)
	{
		_mainMenuWidgetInstance = CreateWidget<UMainMenuWidget>(GetWorld(), _mainMenuWidgetClass);
		if (_mainMenuWidgetInstance != nullptr)
		{
			_mainMenuWidgetInstance->AddToViewport();
		}
	}
}

void AMainMenuHUD::OpenOptions()
{
	if (_optionsWidgetClass)
	{
		_optionsWidgetInstance = CreateWidget<UMainOptionWidget>(GetWorld(), _optionsWidgetClass);
		if (_optionsWidgetInstance != nullptr)
		{
			_optionsWidgetInstance->AddToViewport();
		}
	}
	else
		_optionsWidgetInstance->Open();
}