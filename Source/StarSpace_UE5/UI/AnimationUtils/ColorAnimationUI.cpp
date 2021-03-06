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
	FLinearColor* colorB, int howMuchBlinks, float timeBetwenBlinks, function<void()> callBack)
{
	Button = button;
	ColorA = colorA;
	ColorB = colorB;
	HowMuchBlinks = howMuchBlinks;
	TimeBetwenBlinks = timeBetwenBlinks;
	CallBack = callBack;
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
}

void  ColorAnimationUI::Tick(float DeltaTime)
{
	UIAnimationBase::Tick(DeltaTime);
	if (!_executionHandle.empty())
	{
		ExecuteMap(DeltaTime);
		CleanMap();
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
			if (value->Configuration.CallBack != nullptr)
				value->Configuration.CallBack();
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