// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "MenuBase.h"
#include "../StarSpaceGameState.h"
#include "QuestionModal.h"
#include "MainOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API UMainOptionWidget : public UMenuBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	//When open need to mount the interface using the GameState
	void Open(function<void()> FinisehdAnimationEvent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Music_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SoundFX_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ClearData_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Back_btn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* Music_bool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCheckBox* SoundFX_bool;

private:
	UFUNCTION()
	void Music();
	UFUNCTION()
	void SoundFX();
	UFUNCTION()
	void ClearData();
	UFUNCTION()
	void Back();

	void SyncDataWithMenu();
	void ModalClearDataResponse(QuestionModalResponse modalResponse);
	AStarSpaceGameState* GetGameState();
};
