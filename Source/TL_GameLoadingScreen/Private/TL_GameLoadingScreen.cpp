#include "TL_GameLoadingScreen.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "SThrobber.h"

//定义加载的图片路径
#define LOADING_SCREEN_NAME TEXT("/Game/Res/Start/T_Start_Bg_Logo.T_Start_Bg_Logo")


// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

struct FTL_GameLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FTL_GameLoadingScreenBrush( const FName InTextureName, const FVector2D& InImageSize )
		: FSlateDynamicImageBrush( InTextureName, InImageSize )
	{
		SetResourceObject(LoadObject<UObject>( nullptr, *InTextureName.ToString() ));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		FSlateBrush::AddReferencedObjects(Collector);
	}
};

class STL_LoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STL_LoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		//since we are not using game styles here, just load one image
		LoadingScreenBrush = MakeShareable(new FTL_GameLoadingScreenBrush(LOADING_SCREEN_NAME, FVector2D(1920, 1080)));

		ChildSlot
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(LoadingScreenBrush.Get())
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(10.0f))
				[
					SNew(SThrobber)
					.Visibility(this, &STL_LoadingScreen::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	EVisibility GetLoadIndicatorVisibility() const
	{
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}
	
	/** loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FTL_GameLoadingScreenModule : public ITL_GameLoadingScreenModule
{
public:
	virtual void StartupModule() override
	{		
		// Load for cooker reference
		LoadObject<UObject>(NULL, LOADING_SCREEN_NAME);

		if (IsMoviePlayerEnabled())
		{
			CreateLoadingScreen();
		}
	}


	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen() override
	{
		CreateLoadingScreen();
	}

	void CreateLoadingScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.WidgetLoadingScreen = SNew(STL_LoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
};

IMPLEMENT_GAME_MODULE(FTL_GameLoadingScreenModule, TL_GameLoadingScreen);

