// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include "CoreMinimal.h"
#include "UIAnimationBase.h"
#include "Components/Button.h"
using namespace std;

struct ButtonBlinkConfiguration
{
	UButton* Button;
	FLinearColor* ColorA;
	FLinearColor* ColorB;
	int HowMuchBlinks;
	float TimeBetwenBlinks;
	function<void()> CallBack;	

	ButtonBlinkConfiguration();

	ButtonBlinkConfiguration (UButton* button, FLinearColor* colorA,
		FLinearColor* colorB, int howMuchBlinks, float timeBetwenBlinks, function<void()> callBack);
};

struct ButtonBlinkState
{
	int BlinkCounter;
	float TimeCounter;
	bool Finished;

	ButtonBlinkState();
	
};

struct BlinkButtonHandle
{
	ButtonBlinkConfiguration Configuration;
	ButtonBlinkState State;

	BlinkButtonHandle(ButtonBlinkConfiguration, ButtonBlinkState);
};

class STARSPACE_UE5_API ColorAnimationUI : public UIAnimationBase
{
public:
	void Initialize() override;
	void Tick(float DeltaTime) override;	
	void BlinkButton(ButtonBlinkConfiguration  button);
	void LogOut() override;

private:
	map<int , BlinkButtonHandle*> _executionHandle;

	void ExecuteMap(float DeltaTime);
	void CleanMap();
};
