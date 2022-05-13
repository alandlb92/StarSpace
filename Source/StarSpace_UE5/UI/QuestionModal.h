// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "QuestionModal.generated.h"

/**
 * 
 */

enum QuestionModalResponse
{
	PRYMARY,
	SECONDARY
};

struct QuestionModalConfiguration
{
public:
	FText QuestionText;
	FText PrimaryButtonText;
	FText SecondaryButtonText;
	bool ShowSecondaryButton;
	function<void(QuestionModalResponse)> OnButtonPressed;

	QuestionModalConfiguration(FString questionText, FString primaryButtonText, FString secondaryButtonText, bool showSecondaryButton, function<void(QuestionModalResponse)> onButtonPressed)
	{
		QuestionText = FText::FromString(questionText);
		PrimaryButtonText = FText::FromString(primaryButtonText);
		SecondaryButtonText = FText::FromString(secondaryButtonText);
		ShowSecondaryButton = showSecondaryButton;
		OnButtonPressed = onButtonPressed;
	}
};

UCLASS()
class STARSPACE_UE5_API UQuestionModal : public UMenuBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Primary_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Secondary_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Question_txt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PrimaryResponse_txt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SecondaryResponse_txt;

	void ShowQuestion(QuestionModalConfiguration modalConfiguration);

private:
	function<void(QuestionModalResponse)> OnButtonPressed;
	UFUNCTION()
	void PrimaryButtonPressed();
	UFUNCTION()
	void SecondaryButtonPressed();

};
