// Fill out your copyright notice in the Description page of Project Settings.


#include "StarSpaceGameState.h"
#include "Kismet/GameplayStatics.h"
#include "../LoadingScreen/Public/LoadingScreen.h"


void AStarSpaceGameState::BeginPlay()
{
	Super::BeginPlay();
	LoadGameAsync();
}

void AStarSpaceGameState::SaveState()
{
	SaveGameAsync();
}

void AStarSpaceGameState::SaveGameAsync()
{
	IsLoadingOrSaveData = true;
	USaveGameSlot* SaveGameSlot = Cast<USaveGameSlot>(UGameplayStatics::CreateSaveGameObject(USaveGameSlot::StaticClass()));
	if (SaveGameSlot != nullptr)
	{
		SaveGameSlot->SetGameConfiguration(*GameConfig);
		SaveGameSlot->SetPlayerConfiguration(*PlayerConfig);

		FAsyncSaveGameToSlotDelegate SavedDelegate;
		SavedDelegate.BindUObject(this, &AStarSpaceGameState::OnSaveCompleted);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameSlot, SaveGameSlot->FileName, 0, SavedDelegate);
	}
}

void AStarSpaceGameState::OnSaveCompleted(const FString& SaveNameFile, const int32 UserIndex, bool success)
{
	if (success)
	{
		IsLoadingOrSaveData = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("GameData Saved "));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, SaveNameFile);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error on saved GameData"));

}

void AStarSpaceGameState::LoadGameAsync()
{
	IsLoadingOrSaveData = true;
	USaveGameSlot* SavedGameSlot = Cast<USaveGameSlot>(UGameplayStatics::CreateSaveGameObject(USaveGameSlot::StaticClass()));
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &AStarSpaceGameState::OnLoadCompleted);
	UGameplayStatics::AsyncLoadGameFromSlot(SavedGameSlot->FileName, 0, LoadedDelegate);
}

void AStarSpaceGameState::OnLoadCompleted(const FString& SaveNameFile, const int32 UserIndex, USaveGame* LoadedGame)
{
	if (LoadedGame != nullptr)
	{
		USaveGameSlot* LoadedGameSlot = Cast<USaveGameSlot>(LoadedGame);
		PlayerConfig = new FPlayerConfiguration(LoadedGameSlot->GetPlayerConfiguration());
		GameConfig = new FGameConfiguration(LoadedGameSlot->GetGameConfiguration());
		IsLoadingOrSaveData = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("GameData loaded"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("GameData not found, creating GameData"));
		PlayerConfig = new FPlayerConfiguration();
		GameConfig = new FGameConfiguration();
		SaveGameAsync();
	}
}