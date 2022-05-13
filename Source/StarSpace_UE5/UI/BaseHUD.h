// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "QuestionModal.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class STARSPACE_UE5_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UQuestionModal> _questionModalReference;
	void ShowQuestionModal(QuestionModalConfiguration questionConfig);
	void CloseQuestionModal();

private:
	UQuestionModal* _questionModalInstance;
};
