// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "MenuBase.h"
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Music_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SoundFX_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ClearData_btn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Back_btn;

private:
	UFUNCTION()
	void Music();
	UFUNCTION()
	void SoundFX();
	UFUNCTION()
	void ClearData();
	UFUNCTION()
	void Back();

};
