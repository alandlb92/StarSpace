// Fill out your copyright notice in the Description page of Project Settings.


#include "MainOptionWidget.h"
#include "MainMenuHUD.h"

void UMainOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Music_btn->OnClicked.AddDynamic(this, &UMainOptionWidget::Music);
	SoundFX_btn->OnClicked.AddDynamic(this, &UMainOptionWidget::SoundFX);
	ClearData_btn->OnClicked.AddDynamic(this, &UMainOptionWidget::ClearData);
	Back_btn->OnClicked.AddDynamic(this, &UMainOptionWidget::Back);

	AddButton(Music_btn);
	AddButton(SoundFX_btn);
	AddButton(ClearData_btn);
	AddButton(Back_btn);

	SetInitialState();
}

AStarSpaceGameState* UMainOptionWidget::GetGameState()
{
	return Cast<AStarSpaceGameState>(GetWorld()->GetGameState());
}


void UMainOptionWidget::Open(function<void()> FinisehdAnimationEvent)
{
	Super::Open(FinisehdAnimationEvent);
	SyncDataWithMenu();
}

void UMainOptionWidget::SyncDataWithMenu()
{
	Music_bool->SetCheckedState(GetGameState()->GameConfig->MusicOn ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	SoundFX_bool->SetCheckedState(GetGameState()->GameConfig->SoundFXOn ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}

void UMainOptionWidget::Music()
{
	GetGameState()->GameConfig->MusicOn = !GetGameState()->GameConfig->MusicOn;
	GetGameState()->SaveState();
	SyncDataWithMenu();
	InitializeInputComponent();
}

void UMainOptionWidget::SoundFX()
{
	GetGameState()->GameConfig->SoundFXOn = !GetGameState()->GameConfig->SoundFXOn;
	GetGameState()->SaveState();
	SyncDataWithMenu();
	InitializeInputComponent();
}

void UMainOptionWidget::ClearData()
{
	QuestionModalConfiguration modalConfig =
		QuestionModalConfiguration(TEXT("Are you sure you want to clear all game data?"), TEXT("YES"), TEXT("NO"),
			true, bind(&UMainOptionWidget::ModalClearDataResponse, this, std::placeholders::_1));

	Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowQuestionModal(modalConfig);
}

void UMainOptionWidget::ModalClearDataResponse(QuestionModalResponse modalResponse)
{
	if (modalResponse == QuestionModalResponse::PRYMARY)
	{
	}
	else
	{
	}

	Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->CloseQuestionModal();
	InitializeInputComponent();
}

void UMainOptionWidget::Back()
{
	Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->BackToMain();
}
