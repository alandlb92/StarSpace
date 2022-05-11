// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarSpace_UE5GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../LoadingScreen/Public/LoadingScreen.h"

void AStarSpace_UE5GameModeBase::StartPlay()
{
	//Callet before alls begin play
	Super::StartPlay();
	_UIAnimationUtils = new UIAnimationUtils();

	LoadGameAsync();
}

void AStarSpace_UE5GameModeBase::Logout(AController* Exiting)
{
	UE_LOG(LogTemp, Warning, TEXT("EXTING"));
	_UIAnimationUtils->LogOut();
	delete _UIAnimationUtils;
	_UIAnimationUtils = NULL;
}

void AStarSpace_UE5GameModeBase::SaveGameAsync()
{
	IsLoadingOrSaveData = true;
	USaveGameSlot* SaveGameSlot = Cast<USaveGameSlot>(UGameplayStatics::CreateSaveGameObject(USaveGameSlot::StaticClass()));
	if (SaveGameSlot != nullptr)
	{
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		SavedDelegate.BindUObject(this, &AStarSpace_UE5GameModeBase::OnSaveCompleted);

		SaveGameSlot->SetGameConfiguration(*GameConfig);
		SaveGameSlot->SetPlayerConfiguration(*PlayerConfig);

		UGameplayStatics::AsyncSaveGameToSlot(SaveGameSlot, SaveGameSlot->FileName, 0, SavedDelegate);
	}
}

void AStarSpace_UE5GameModeBase::OnSaveCompleted(const FString& SaveNameFile, const int32 UserIndex, bool success)
{
	if (success)
	{
		IsLoadingOrSaveData = false;
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error on saved GameData"));

}

void AStarSpace_UE5GameModeBase::LoadGameAsync()
{
	IsLoadingOrSaveData = true;
	USaveGameSlot* SavedGameSlot = Cast<USaveGameSlot>(UGameplayStatics::CreateSaveGameObject(USaveGameSlot::StaticClass()));
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &AStarSpace_UE5GameModeBase::OnLoadCompleted);
	UGameplayStatics::AsyncLoadGameFromSlot(SavedGameSlot->FileName, 0, LoadedDelegate);	
}

void AStarSpace_UE5GameModeBase::OnLoadCompleted(const FString& SaveNameFile, const int32 UserIndex, USaveGame* LoadedGame)
{
	if (LoadedGame != nullptr)
	{
		USaveGameSlot* LoadedGameSlot = Cast<USaveGameSlot>(LoadedGame);
		PlayerConfig = new PlayerConfiguration(LoadedGameSlot->GetPlayerConfiguration());
		GameConfig = new GameConfiguration(LoadedGameSlot->GetGameConfiguration());
		IsLoadingOrSaveData = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("GameData loaded"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("GameData not foun, creating GameData"));
		PlayerConfig = new PlayerConfiguration();
		GameConfig = new GameConfiguration();
		SaveGameAsync();
	}
}