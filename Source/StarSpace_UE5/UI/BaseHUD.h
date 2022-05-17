// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AnimationUtils/UIAnimationUtils.h"
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
	virtual void BeginPlay() override;
	UIAnimationUtils* GetUIAnimationUtils() { return _UIAnimationUtils; }
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UQuestionModal> _questionModalReference;
	void ShowQuestionModal(QuestionModalConfiguration questionConfig);
	void CloseQuestionModal();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	UQuestionModal* _questionModalInstance;
	UIAnimationUtils* _UIAnimationUtils;
};
