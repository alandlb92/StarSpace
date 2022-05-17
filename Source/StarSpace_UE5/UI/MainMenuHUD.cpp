// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"


void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if (_mainMenuWidgetClass)
	{
		if (_mainMenuWidgetInstance == nullptr)
			_mainMenuWidgetInstance = CreateWidget<UMainMenuWidget>(GetWorld(), _mainMenuWidgetClass);
		if (_mainMenuWidgetInstance != nullptr)
		{
			_mainMenuWidgetInstance->AddToViewport();
			_mainMenuWidgetInstance->Open(NULL);
		}
	}
}

void AMainMenuHUD::OpenOptions()
{
	if (_optionsWidgetClass)
	{
		if (_optionsWidgetInstance == nullptr)
			_optionsWidgetInstance = CreateWidget<UMainOptionWidget>(GetWorld(), _optionsWidgetClass);
		if (_optionsWidgetInstance != nullptr)
		{
			_optionsWidgetInstance->AddToViewport();
		}
	}

	if (_mainMenuWidgetInstance != nullptr)
		_mainMenuWidgetInstance->Close([this]() -> void {
		if (_optionsWidgetInstance != nullptr)
			_optionsWidgetInstance->Open(NULL);});
}

void AMainMenuHUD::BackToMain()
{
	if (_optionsWidgetInstance != nullptr)
		_optionsWidgetInstance->Close([this]() -> void {
	if (_mainMenuWidgetInstance != nullptr)
		_mainMenuWidgetInstance->Open(NULL);});
}