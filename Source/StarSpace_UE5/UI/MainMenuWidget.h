// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"
#include "Components/Button.h"
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
	UButton* NewGame_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* LoadGame_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Options_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Exit_btn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor NormalColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor SelectedColor;

protected:
	void InitializeInputComponent() override;

private:
	TArray<UButton*> _buttons;
	UButton* _buttonSelected;
	bool _canMoveMenu = true;

	void CaptureAxis(float);

	void SetButtonSelected(UButton*);
	void UpdateButtonSelectedStyles();
	void SelectDownMenuOption();
	void SelectUpMenuOption();

	void NewGame();
	void LoadGame();
	void Options();
	void Exit();
};
