// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuWidget.h"
#include "MainOptionWidget.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	void OpenOptions();
	void BackToMain();
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenuWidget> _mainMenuWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainOptionWidget> _optionsWidgetClass;

private:
	UMainMenuWidget* _mainMenuWidgetInstance;
	UMainOptionWidget* _optionsWidgetInstance;
};
