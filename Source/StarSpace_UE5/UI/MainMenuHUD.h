// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuWidget.h"
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
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> _mainMenuWidgetClass;

private:
	UMainMenuWidget* _mainMenuWidget;
};
