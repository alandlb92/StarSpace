// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"
#include "Components/Button.h"
#include "AnimationUtils/ColorAnimationUI.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API UMainMenuWidget : public UUserWidget
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor NormalColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor SelectedColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor BlinkColor;


protected:
	UFUNCTION(BluePrintCallable, category = "Main Menu Widget")
	void InitializeInputComponent() override;


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

	UFUNCTION()
	void PlayGame();
	UFUNCTION()
	void Options();
	UFUNCTION()
	void Exit();
};
