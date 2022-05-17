// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"



void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	_UIAnimationUtils = new UIAnimationUtils();
}

void ABaseHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (_UIAnimationUtils != nullptr)
		_UIAnimationUtils->LogOut();
}

void ABaseHUD::ShowQuestionModal(QuestionModalConfiguration questionConfig)
{
	if (_questionModalReference)
	{
		if (_questionModalInstance == nullptr)
			_questionModalInstance = CreateWidget<UQuestionModal>(GetWorld(), _questionModalReference);
		if (_questionModalInstance != nullptr)
		{
			_questionModalInstance->AddToViewport();
		}
	}

	if (_questionModalInstance != nullptr)
		_questionModalInstance->ShowQuestion(questionConfig);
}

void ABaseHUD::CloseQuestionModal()
{
	if (_questionModalInstance != nullptr)
		_questionModalInstance->Close(NULL);
}