// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnimationUtils/ColorAnimationUI.h"
#include "Math/Color.h"
#include "Components/Button.h"
#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor NormalColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor SelectedColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor BlinkColor;


	virtual void Open(function<void()> FinisehdAnimationEvent);
	virtual void Close(function<void()> FinisehdAnimationEvent);

	UFUNCTION(BlueprintImplementableEvent)
	void CallOpenAnimation();
	UFUNCTION(BlueprintImplementableEvent)
	void CallCloseAnimation();


protected:
	UFUNCTION(BluePrintCallable, category = "Menu Base Widget")
	void InitializeInputComponent() override;
	UFUNCTION(BluePrintCallable, category = "Menu Base Widget")
	virtual void OnOpenAnimationStarted();
	UFUNCTION(BluePrintCallable, category = "Menu Base Widget")
	virtual void OnOpenAnimationEnded();
	
	void ClearInputComponent();
	void AddButton(UButton*);
	void SetInitialState();

private:
	TArray<UButton*> _buttons;
	UButton* _buttonSelected;
	bool _canMoveMenu = true;

	void CaptureAxis(float);
	void SelectButton();

	void SetButtonSelected(UButton*);
	void UpdateButtonSelectedStyles();
	void SelectDownMenuOption();
	void SelectUpMenuOption();
	void CallSelectedButtonAction();
	ColorAnimationUI* GetAnimationUtils();

	function<void()> AnimationStartedEvent = NULL;
	function<void()> AnimationEndedEvent = NULL;
};
