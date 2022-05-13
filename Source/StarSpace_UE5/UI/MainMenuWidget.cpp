
#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuHUD.h"
#include "../StarSpace_UE5GameModeBase.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayGame_btn->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
	Options_btn->OnClicked.AddDynamic(this, &UMainMenuWidget::Options);
	Exit_btn->OnClicked.AddDynamic(this, &UMainMenuWidget::Exit);

	AddButton(PlayGame_btn);
	AddButton(Options_btn);
	AddButton(Exit_btn);
	SetInitialState();
}

void UMainMenuWidget::PlayGame()
{
	//loading
	Close(NULL);
	ILoadingScreenModule& LoadingScreenModule = ILoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(true, 50);
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UGameplayStatics::OpenLevel(GameInstance, FName("GamePlay"));
}

void UMainMenuWidget::Options()
{
	Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->OpenOptions();
}

void UMainMenuWidget::Exit()
{
	QuestionModalConfiguration modalConfig = 
	QuestionModalConfiguration(TEXT("Are you sure you want to quit the game?"), TEXT("YES"), TEXT("NO"), 
		true, bind(&UMainMenuWidget::ModalExitResponse, this, std::placeholders::_1));

	Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowQuestionModal(modalConfig);
}

void UMainMenuWidget::ModalExitResponse(QuestionModalResponse modalResponse)
{
	if (modalResponse == QuestionModalResponse::PRYMARY)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	}
	else
	{
		Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->CloseQuestionModal();
		InitializeInputComponent();
	}
}