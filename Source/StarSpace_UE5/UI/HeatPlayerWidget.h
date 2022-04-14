// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeatPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API UHeatPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHeatPlayerWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void UpdateHeatPlayer(float value);
	void UpdateOverHeatPlayer(float value);
	 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* _heatProgress;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* _overHeatProgress;
};
