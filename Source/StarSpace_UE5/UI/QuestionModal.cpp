// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestionModal.h"


void UQuestionModal::NativeConstruct()
{
	Super::NativeConstruct();

	Primary_btn->OnClicked.AddDynamic(this, &UQuestionModal::PrimaryButtonPressed);
	Secondary_btn->OnClicked.AddDynamic(this, &UQuestionModal::SecondaryButtonPressed);

	AddButton(Primary_btn);
	AddButton(Secondary_btn);

	SetInitialState();
}

void UQuestionModal::ShowQuestion(QuestionModalConfiguration modalConfiguration)
{
	Question_txt->SetText(modalConfiguration.QuestionText);
	PrimaryResponse_txt->SetText(modalConfiguration.PrimaryButtonText);
	SecondaryResponse_txt->SetText(modalConfiguration.SecondaryButtonText);
	Secondary_btn->SetVisibility(modalConfiguration.ShowSecondaryButton ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	OnButtonPressed = modalConfiguration.OnButtonPressed;
	Open(NULL);
}


void UQuestionModal::PrimaryButtonPressed()
{
	if (OnButtonPressed)
		OnButtonPressed(QuestionModalResponse::PRYMARY);

	OnButtonPressed = NULL;
}

void UQuestionModal::SecondaryButtonPressed()
{
	if (OnButtonPressed)
		OnButtonPressed(QuestionModalResponse::SECONDARY);

	OnButtonPressed = NULL;
}