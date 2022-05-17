// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	if (_heatPlayerWidgetClass)
	{
		_heatPlayerWidget = CreateWidget<UHeatPlayerWidget>(GetWorld(), _heatPlayerWidgetClass);
		if (_heatPlayerWidget != nullptr)
		{
			_heatPlayerWidget->AddToViewport();
		}
	}
}
void APlayerHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();
}

void APlayerHUD::UpdatePlayerHeat(int currentHeat, int maxHeat)
{
	float currentHeatFloat = currentHeat;
	float maxHeatFloat = maxHeat;

	float currentHeatPercentage = currentHeatFloat / maxHeatFloat;

	float heatPercentage = currentHeatPercentage >= 0.5f ? 1.0f : currentHeatPercentage * 2;
	float overHeatPercentage = currentHeatPercentage < 0.5f ? 0.0f : (currentHeatPercentage - 0.5f) * 2;

	_heatPlayerWidget->UpdateHeatPlayer(heatPercentage);
	_heatPlayerWidget->UpdateOverHeatPlayer(overHeatPercentage);
}

