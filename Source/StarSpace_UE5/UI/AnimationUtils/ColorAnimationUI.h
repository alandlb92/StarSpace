// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIAnimationBase.h"

class STARSPACE_UE5_API ColorAnimationUI : public UIAnimationBase
{
public:
	void Initialize() override;
	void Tick(float DeltaTime) override;
};
