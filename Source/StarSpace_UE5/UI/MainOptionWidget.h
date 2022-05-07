// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API UMainOptionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Open();
	void Close();

	UFUNCTION(BlueprintImplementableEvent)
	void CallOpenAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void CallCloseAnimation();
};
