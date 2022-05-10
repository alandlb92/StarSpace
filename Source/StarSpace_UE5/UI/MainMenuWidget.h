// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"
#include "MenuBase.h"
#include "Components/Button.h"
#include "AnimationUtils/ColorAnimationUI.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API UMainMenuWidget : public UMenuBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PlayGame_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Options_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Exit_btn;

private:
	UFUNCTION()
	void PlayGame();
	UFUNCTION()
	void Options();
	UFUNCTION()
	void Exit();
};
