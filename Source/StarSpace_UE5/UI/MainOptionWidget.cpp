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

void UMainOptionWidget::Music()
{
	InitializeInputComponent();
}

void UMainOptionWidget::SoundFX()
{
	InitializeInputComponent();
}

void UMainOptionWidget::ClearData()
{
	InitializeInputComponent();
}

void UMainOptionWidget::Back()
{
	Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->BackToMain();
}