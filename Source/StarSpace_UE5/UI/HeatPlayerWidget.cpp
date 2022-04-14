// Fill out your copyright notice in the Description page of Project Settings.


#include "HeatPlayerWidget.h"
#include "Components/ProgressBar.h"

UHeatPlayerWidget::UHeatPlayerWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHeatPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHeatPlayerWidget::UpdateHeatPlayer(float value)
{
	if (_heatProgress != nullptr)
	{
		_heatProgress->SetPercent(value);
	}
}

void UHeatPlayerWidget::UpdateOverHeatPlayer(float value)
{
	if (_overHeatProgress != nullptr)
	{
		_overHeatProgress->SetPercent(value);
	}
}