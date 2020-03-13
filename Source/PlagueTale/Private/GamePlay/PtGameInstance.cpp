// Fill out your copyright notice in the Description page of Project Settings.


#include "PtGameInstance.h"
#include "MoviePlayer/Public/MoviePlayer.h"
#include "ConstructorHelpers.h"
#include "PtLoadUserWidget.h"

#include "CircularThrobber.h"
#include "TextBlock.h"
#include "Button.h"


/** 初始化方法 */
void UPTGameInstance::Init()
{
	UGameInstance::Init();

	//开始加载地图的委托
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UPTGameInstance::PreLoadMap);
	//结束加载地图的委托
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UPTGameInstance::PostLoadMap);

	//初始化加载Widget
	LoadWidget = CreateWidget<UPtLoadUserWidget>(this, LoadClass<UPtLoadUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/PTLoadUserWidget_BP.PTLoadUserWidget_BP_C'")));
}

/** 地图加载开始的方法 */
void UPTGameInstance::PreLoadMap(const FString& Map)
{
	//判断是否是加载的主关卡//暂时加载关卡都要显示load界面
	//if (Map.Equals("/Game/Map/Map_Main"))
	{
		//创建一个屏幕加载属性对象
		FLoadingScreenAttributes LoadingAttr;
		//手动的点击跳过加载
		LoadingAttr.bWaitForManualStop = true;
		//设置加载的Widget
		LoadingAttr.WidgetLoadingScreen = LoadWidget->TakeWidget();
		//设置开始加载
		LoadWidget->SetStartLoad();
		//设置加载屏幕
		GetMoviePlayer()->SetupLoadingScreen(LoadingAttr);
	}
}

/** 地图加载结束的方法 */
void UPTGameInstance::PostLoadMap(UWorld* World)
{
}

/** 是否加载完成 */
bool UPTGameInstance::GetLoadStatus()
{
	//返回是否已经加载完成
	return GetMoviePlayer()->IsLoadingFinished();
}

