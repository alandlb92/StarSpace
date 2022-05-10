
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
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UGameplayStatics::OpenLevel(GameInstance, FName("GamePlay"));
	//loading
	/*ILoadingScreenModule& LoadingScreenModule = ILoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(false, 5);*/
}

void UMainMenuWidget::Options()
{
	Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->OpenOptions();
}

void UMainMenuWidget::Exit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}