// Copyright Epic Games, Inc. All Rights Reserved.

#include "../Public/LoadingScreen.h"
#include "Modules/ModuleManager.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"


struct LoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	LoadingScreenBrush(const FName InTextureName, const FVector2d& InImageSize) : FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject* CachedResourceObject = GetResourceObject())
		{
			Collector.AddReferencedObject(CachedResourceObject);
		}
	}
};


class LoadingScreen : public SCompoundWidget
{
private:
	/** Rather to show the ... indicator */
	EVisibility GetLoadIndicatorVisibility() const
	{
		bool Vis = GetMoviePlayer()->IsLoadingFinished();
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}
	TSharedPtr<FSlateDynamicImageBrush> LoadingImageBrush;

public:
	SLATE_BEGIN_ARGS(LoadingScreen) {}
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs)
	{
		static const FName LoadingScreenName(TEXT("/Game/Textures/ui/StarSpaceLogo.StarSpaceLogo"));	
		LoadingImageBrush = MakeShareable(new LoadingScreenBrush(LoadingScreenName, FVector2D(1024, 256)));

		FSlateBrush* BGBrush = new FSlateBrush();
		BGBrush->TintColor = FLinearColor(0.034f, 0.034f, 0.034f, 1.0f);

		ChildSlot
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.BorderImage(BGBrush)
			]
		+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(LoadingImageBrush.Get())
			]
		+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(FMargin(10.0f))
			[
				SNew(SThrobber)
				.Visibility(this, &LoadingScreen::GetLoadIndicatorVisibility)
			]
			]
			];
	}

};


class FLoadingScreenModule : public ILoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("StartupModule"));
		// Force load for cooker reference
		LoadObject<UObject>(nullptr, TEXT("/Game/Textures/ui/StarSpaceLogo.StarSpaceLogo"));

		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	{
		FLoadingScreenAttributes LoadingScreenInstance;
		LoadingScreenInstance.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
		LoadingScreenInstance.bWaitForManualStop = bPlayUntilStopped;
		LoadingScreenInstance.bAllowEngineTick = bPlayUntilStopped;
		LoadingScreenInstance.MinimumLoadingScreenDisplayTime = PlayTime;
		LoadingScreenInstance.WidgetLoadingScreen = SNew(LoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreenInstance);
	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreenInstance;
		LoadingScreenInstance.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreenInstance.MinimumLoadingScreenDisplayTime = 3.f;
		LoadingScreenInstance.WidgetLoadingScreen = SNew(LoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreenInstance);
	}

};

IMPLEMENT_GAME_MODULE( FLoadingScreenModule, LoadingScreen );
