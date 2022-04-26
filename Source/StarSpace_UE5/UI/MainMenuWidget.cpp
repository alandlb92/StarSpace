
#include "MainMenuWidget.h"
#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	NewGame_btn->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGame);
	LoadGame_btn->OnClicked.AddDynamic(this, &UMainMenuWidget::LoadGame);
	Options_btn->OnClicked.AddDynamic(this, &UMainMenuWidget::Options);
	Exit_btn->OnClicked.AddDynamic(this, &UMainMenuWidget::Exit);

	_buttons.Add(NewGame_btn);
	_buttons.Add(LoadGame_btn);
	_buttons.Add(Options_btn);
	_buttons.Add(Exit_btn);

	SetButtonSelected(_buttons[0]);
	UpdateButtonSelectedStyles();

	InitializeInputComponent();
}

void UMainMenuWidget::InitializeInputComponent()
{
	Super::InitializeInputComponent();
	InputComponent->BindAxis("MoveY", this, &UMainMenuWidget::CaptureAxis);
}

void UMainMenuWidget::CaptureAxis(float value)
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

	UE_LOG(LogTemp, Warning, TEXT("CaptureAxis %f"), value);
}

void UMainMenuWidget::SetButtonSelected(UButton* buttonSelected)
{
	_buttonSelected = buttonSelected;
}

void UMainMenuWidget::UpdateButtonSelectedStyles()
{
	for (auto Btn : _buttons)
	{
		if (Btn == _buttonSelected)
			Btn->SetColorAndOpacity(SelectedColor);
		else
			Btn->SetColorAndOpacity(NormalColor);
	}

}

void UMainMenuWidget::SelectDownMenuOption()
{
	int nextIndex = _buttons.Last() == _buttonSelected ? 0
		: _buttons.IndexOfByKey(_buttonSelected) + 1;

	SetButtonSelected(_buttons[nextIndex]);
	UpdateButtonSelectedStyles();
}

void UMainMenuWidget::SelectUpMenuOption()
{
	int previousIndex = _buttons[0] == _buttonSelected ? _buttons.Num() - 1 
		: _buttons.IndexOfByKey(_buttonSelected) - 1;

	SetButtonSelected(_buttons[previousIndex]);
	UpdateButtonSelectedStyles();
}

void UMainMenuWidget::NewGame()
{
	UE_LOG(LogTemp, Warning, TEXT("NEW GAME"));
}

void UMainMenuWidget::LoadGame()
{
	UE_LOG(LogTemp, Warning, TEXT("LOAD GAME"));
}

void UMainMenuWidget::Options()
{
	UE_LOG(LogTemp, Warning, TEXT("OPTIONS"));
}

void UMainMenuWidget::Exit()
{
	UE_LOG(LogTemp, Warning, TEXT("EXIT"));
}