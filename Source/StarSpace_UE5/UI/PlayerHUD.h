// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "HeatPlayerWidget.h"
#include "BaseHUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API APlayerHUD : public ABaseHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdatePlayerHeat(int currentHeat, int maxHeat);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> _heatPlayerWidgetClass;

private:
	UHeatPlayerWidget* _heatPlayerWidget;
};
