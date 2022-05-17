// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuBase.h"
#include "../StarSpace_UE5GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BaseHUD.h"

void UMenuBase::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UMenuBase::Open(function<void()> FinisehdOpenAnimationEvent)
{
	CallOpenAnimation();
	SetVisibility(ESlateVisibility::Visible);
	InitializeInputComponent();
	AnimationEndedEvent = FinisehdOpenAnimationEvent;
}

void UMenuBase::Close(function<void()> FinisehdCloseAnimationEvent)
{
	ClearInputComponent();
	CallCloseAnimation();
	AnimationStartedEvent = FinisehdCloseAnimationEvent;
}

void UMenuBase::AddButton(UButton* button)
{
	_buttons.Add(button);
}

void UMenuBase::SetInitialState()
{
	SetButtonSelected(_buttons[0]);
	UpdateButtonSelectedStyles();
}

void UMenuBase::OnOpenAnimationStarted()
{
	if (AnimationStartedEvent != NULL)
	{
		AnimationStartedEvent();
		AnimationStartedEvent = NULL;
	}
}

void UMenuBase::OnOpenAnimationEnded()
{
	if (AnimationEndedEvent != NULL)
	{
		AnimationEndedEvent();
		AnimationEndedEvent = NULL;
	}
}

void UMenuBase::InitializeInputComponent()
{
	Super::InitializeInputComponent();
	if (isHorizontalMenu)
		InputComponent->BindAxis("MoveX", this, &UMenuBase::CaptureAxis);
	else
		InputComponent->BindAxis("MoveY", this, &UMenuBase::CaptureAxis);

	InputComponent->BindAction("Shoot", IE_Pressed, this, &UMenuBase::SelectButton);
}

void UMenuBase::ClearInputComponent()
{
	InputComponent->ClearActionBindings();
	InputComponent->AxisBindings.Empty();
}

void UMenuBase::CaptureAxis(float value)
{
	if (value > 0.1f && _canMoveMenu)
	{
		SelectUpMenuOption();
		_canMoveMenu = false;
	}
	else if (value < -0.1f && _canMoveMenu)
	{
		SelectDownMenuOption();
		_canMoveMenu = false;
	}
	else if (value > -0.1f && value < 0.1f)
		_canMoveMenu = true;
}

void UMenuBase::SelectButton()
{
	ClearInputComponent();
	ButtonBlinkConfiguration blinkConfig = ButtonBlinkConfiguration(_buttonSelected, &SelectedColor, &BlinkColor, 5, 0.1f, bind(&UMenuBase::CallSelectedButtonAction, this));
	ColorAnimationUI* animUtils = GetAnimationUtils();
	if (animUtils != nullptr)
		animUtils->BlinkButton(blinkConfig);
}

void UMenuBase::SetButtonSelected(UButton* buttonSelected)
{
	_buttonSelected = buttonSelected;
}

void UMenuBase::UpdateButtonSelectedStyles()
{
	for (auto Btn : _buttons)
	{
		if (Btn == _buttonSelected)
			Btn->SetColorAndOpacity(SelectedColor);
		else
			Btn->SetColorAndOpacity(NormalColor);
	}
}

void UMenuBase::SelectDownMenuOption()
{
	int nextIndex = _buttons.Last() == _buttonSelected ? 0
		: _buttons.IndexOfByKey(_buttonSelected) + 1;

	SetButtonSelected(_buttons[nextIndex]);
	UpdateButtonSelectedStyles();
}

void UMenuBase::SelectUpMenuOption()
{
	int previousIndex = _buttons[0] == _buttonSelected ? _buttons.Num() - 1
		: _buttons.IndexOfByKey(_buttonSelected) - 1;

	SetButtonSelected(_buttons[previousIndex]);
	UpdateButtonSelectedStyles();
}

void UMenuBase::CallSelectedButtonAction()
{
	_buttonSelected->OnClicked.Broadcast();
}

ColorAnimationUI* UMenuBase::GetAnimationUtils()
{
	ABaseHUD* baseHud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (baseHud != nullptr)
	{
		UIAnimationUtils* AnimationUtils = baseHud->GetUIAnimationUtils();
		if (AnimationUtils != nullptr)
		{
			return AnimationUtils->GetColorAnimationUI();
		}
	}
	return nullptr;
}