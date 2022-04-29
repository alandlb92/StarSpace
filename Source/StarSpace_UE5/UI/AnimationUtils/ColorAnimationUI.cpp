// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorAnimationUI.h"
#include <vector>
#include "../../Utils/IdUtils.h"

BlinkButtonHandle::BlinkButtonHandle(ButtonBlinkConfiguration configuration, ButtonBlinkState state)
{
	Configuration = configuration;
	State = state;

}

ButtonBlinkConfiguration::ButtonBlinkConfiguration() {}

ButtonBlinkConfiguration::ButtonBlinkConfiguration(UButton* button, FLinearColor* colorA,
	FLinearColor* colorB, int howMuchBlinks, float timeBetwenBlinks)
{
	Button = button;
	ColorA = colorA;
	ColorB = colorB;
	HowMuchBlinks = howMuchBlinks;
	TimeBetwenBlinks = timeBetwenBlinks;
}

ButtonBlinkState::ButtonBlinkState()
{
	BlinkCounter = 0;
	TimeCounter = 0;
	Finished = false;
}

void ColorAnimationUI::Initialize()
{
	UIAnimationBase::Initialize();
	UE_LOG(LogTemp, Warning, TEXT("ColorAnimationUI::Initialize"));	
}

void  ColorAnimationUI::Tick(float DeltaTime)
{
	UIAnimationBase::Tick(DeltaTime);
	if (!_executionHandle.empty())
	{
		ExecuteMap(DeltaTime);
		UE_LOG(LogTemp, Warning, TEXT("Count Of Map %i"), _executionHandle.size());
		CleanMap();
		UE_LOG(LogTemp, Warning, TEXT("Count Of Map %i"), _executionHandle.size());
	}
}

void ColorAnimationUI::ExecuteMap(float DeltaTime)
{
	for (auto [key, value] : _executionHandle)
	{
		if (value->State.BlinkCounter >= value->Configuration.HowMuchBlinks)
		{
			value->State.Finished = true;
			continue;
		}
		
		value->State.TimeCounter += DeltaTime;

		if (value->State.TimeCounter >= value->Configuration.TimeBetwenBlinks)
		{
			value->State.TimeCounter = 0;
			value->Configuration.Button
				->SetColorAndOpacity(
					value->Configuration.Button->ColorAndOpacity.Equals(*value->Configuration.ColorA)
					? *value->Configuration.ColorB : *value->Configuration.ColorA);
			value->State.BlinkCounter++;
		}
	}
}

void ColorAnimationUI::CleanMap()
{
	vector<int> toRemove;
	for (auto [key, value] : _executionHandle)
	{
		if (value->State.Finished) {
			toRemove.push_back(key);
			delete value;
			value = NULL;
		}
	}

	for (auto key : toRemove)
	{
		_executionHandle.erase(key);
	}
}

void ColorAnimationUI::BlinkButton(ButtonBlinkConfiguration  buttonBlinkConfiguration)
{
	buttonBlinkConfiguration.Button->SetColorAndOpacity(*buttonBlinkConfiguration.ColorB);
	ButtonBlinkState blinkState = ButtonBlinkState();
	BlinkButtonHandle* handle = new BlinkButtonHandle(buttonBlinkConfiguration, blinkState);	
	_executionHandle.insert(pair<int, BlinkButtonHandle*>(IdUtils::GetNewId(), handle));
}

void ColorAnimationUI::LogOut()
{
	for (auto [key, value] : _executionHandle)
	{
		value->State.Finished = true;
	}
	CleanMap();
}