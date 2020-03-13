// Fill out your copyright notice in the Description page of Project Settings.


#include "PtLoginUserWidget.h"
#include "Button.h"
#include "TextBlock.h"
#include "EditableTextBox.h"
#include "PtMessageUserWidget.h"
#include "Components/CircularThrobber.h"

#include "JsonWriter.h"
#include "JsonObject.h"
#include "JsonReader.h"
#include "JsonSerializer.h"
#include "CondensedJsonPrintPolicy.h"
#include "PtGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/KBEMain.h"
#include "PtStartGameMode.h"


/** 控件创建完成的初始化方法 */
bool UPtLoginUserWidget::Initialize()
{
	if (!Super::Initialize())return false;

	//初始化返回按钮
	BackBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Back")));
	//初始化昵称输入框
	NicknameInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Nickname")));
	//初始化密码输入框
	PasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Password")));
	//初始化登录按钮
	LoginBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Login")));

	//注册登录按钮点击事件
	LoginBtn->OnClicked.AddDynamic(this, &UPtLoginUserWidget::OnLoginBtnOnClicked);

	//初始化进度条控件
	CircularThrobber = Cast<UCircularThrobber>(GetWidgetFromName(TEXT("CircularThrobber_Loading")));
	//初始化信息提示框
	MessageUserWidget = Cast<UPtMessageUserWidget>(GetWidgetFromName(TEXT("Message_Box")));

	return true;
}

/** 登录按钮点击事件 */
void UPtLoginUserWidget::OnLoginBtnOnClicked()
{
	//获取用户输入的昵称
	FString Nickname = NicknameInput->GetText().ToString();
	//获取用户输入的密码
	FString Password = PasswordInput->GetText().ToString();

	//校验昵称是否为空
	if (Nickname.IsEmpty())
	{
		//提示信息
		MessageUserWidget->MsgBlock->SetText(FText::FromString("Nickname Is Empty"));
		MessageUserWidget->SetVisibility(ESlateVisibility::Visible);

		return;
	}

	//校验密码是否为空 
	if (Password.IsEmpty())
	{
		//提示信息
		MessageUserWidget->MsgBlock->SetText(FText::FromString("Password Is Empty"));
		MessageUserWidget->SetVisibility(ESlateVisibility::Visible);

		return;
	}

	//可以填任意二进制数据
	TArray<uint8> LoginData;
	FString ProjectName("PlagueTale");
	for (int i = 0; i < ProjectName.Len(); ++i) {
		LoginData.Push((uint8)ProjectName[i]);
	}

	//用户登录
	APtStartGameMode* SGM = Cast<APtStartGameMode>(UGameplayStatics::GetGameMode(this));
	if (SGM) {
		SGM->KBEMain->login(Nickname, Password, LoginData);
	}

	//用户登录
	//AccountLoginFromServer(Nickname, Password);

	//加载进度条显示
	//CircularThrobber->SetVisibility(ESlateVisibility::Visible);

	//登录按钮设置不可用
	LoginBtn->SetIsEnabled(false);
}

/** 用户登录的方法 */
void UPtLoginUserWidget::AccountLoginFromServer(FString Nickname, FString Password)
{

	//暂时直接进行关卡的切换 ！！！！！！！！！！！！！！！！！！！！！！！
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Map/Map_Main"));
	return;
	//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！


	//提交的Json
	FString Data;
	//创建Json写入器
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Data);
	//打开写入
	JsonWriter->WriteObjectStart();
	//写入昵称
	JsonWriter->WriteValue("nickname", Nickname);
	//写入密码
	JsonWriter->WriteValue("password", Password);
	//关闭写入
	JsonWriter->WriteObjectEnd();
	//关闭Json写入器
	JsonWriter->Close();

	//创建HTTP请求 
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	//设置请求头
	Request->SetHeader("Content-Type", "application/json;charset=utf-8");
	//设置请求方式
	Request->SetVerb("POST");
	//设置请求的内容
	Request->SetContentAsString(Data);
	//请求的URL
	Request->SetURL("http://www.xxx.com:7900/user/login-user");
	//设置请求成功的回调方法
	Request->OnProcessRequestComplete().BindUObject(this, &UPtLoginUserWidget::RequestComplete);
	//开始处理请求
	Request->ProcessRequest();
}

/** 请求的响应方法 */
void UPtLoginUserWidget::RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess)
{
	//加载框设置隐藏
	CircularThrobber->SetVisibility(ESlateVisibility::Hidden);
	//设置登录按钮可用状态
	LoginBtn->SetIsEnabled(true);

	//判断响应的状态
	if (!ResponsePtr||!EHttpResponseCodes::IsOk(ResponsePtr->GetResponseCode()))
	{
		return;
	}

	//创建Json解析器
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponsePtr->GetContentAsString());
	//创建Json对象
	TSharedPtr<FJsonObject> JsonObject;
	//反序列化Json
	bool bIsOk = FJsonSerializer::Deserialize(JsonReader, JsonObject);
	//判断是否反序列化成功
	if (bIsOk)
	{
		//获取返回数据的msg
		FString Msg = JsonObject->GetStringField("msg");

		//获取返回的数据的data
		TSharedPtr<FJsonObject> JsonData = JsonObject->GetObjectField("data");
		//从data中获取用户的id
		FString Id = JsonData->GetStringField("id");
		//从data中获取用户的nickname
		FString Nickname = JsonData->GetStringField("nickname");
		//判断nickname是否为空
		if (!Nickname.IsEmpty())
		{
			//获取到自定义的GameInstance
			UPTGameInstance* GameInstace = Cast<UPTGameInstance>(GetWorld()->GetGameInstance());
			//把id保存到GameInstance
			GameInstace->ContextMap.Add("id", Id);
			//关卡的切换
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Map/Map_Main"));
		}
		else
		{
			//提示信息
			MessageUserWidget->MsgBlock->SetText(FText::FromString(Msg));
			MessageUserWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
