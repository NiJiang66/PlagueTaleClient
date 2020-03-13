// Fill out your copyright notice in the Description page of Project Settings.


#include "PtGameModeBase.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtCommon.h"
#include "TimerManager.h"


APtGameModeBase::APtGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APtGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	InstallEvents();
}

void APtGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnInstallEvents();
}

void APtGameModeBase::InstallEvents()
{
	//注册最基本的回调事件,KBEventTypes.cpp
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);//被踢出
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);//断线
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState);//当前连接状态
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);//断线重连
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);//重连失败
}

void APtGameModeBase::UnInstallEvents()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void APtGameModeBase::OnKicked(const UKBEventData* pEventData)
{
	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(pEventData);

	PtH::Debug() << "OnDisconnected : eventName --> " << ServerData->eventName << PtH::Endl();
}

void APtGameModeBase::OnDisconnected(const UKBEventData* pEventData)
{
	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(pEventData);

	PtH::Debug() << "OnDisconnected : eventName --> " << ServerData->eventName << PtH::Endl();
}

void APtGameModeBase::OnConnectionState(const UKBEventData* pEventData)
{
	const UKBEventData_onConnectionState* ServerData = Cast<UKBEventData_onConnectionState>(pEventData);

	PtH::Debug() << "OnConnectionState : success --> " << ServerData->success << " ; address --> " << ServerData->address << PtH::Endl();
}

void APtGameModeBase::OnReloginBaseappSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onReloginBaseappSuccessfully* ServerData = Cast<UKBEventData_onReloginBaseappSuccessfully>(pEventData);

	PtH::Debug() << "OnReloginBaseappSuccessfully : eventName --> " << ServerData->eventName << PtH::Endl();
}

void APtGameModeBase::OnReloginBaseappFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onReloginBaseappFailed* ServerData = Cast<UKBEventData_onReloginBaseappFailed>(pEventData);

	PtH::Debug() << "OnReloginBaseappFailed : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << PtH::Endl();
}


void APtGameModeBase::StartReloginBaseappTimer()
{
	if (!TimerHandle.IsValid()) {
		GetWorldTimerManager().SetTimer(TimerHandle, this, &APtGameModeBase::OnReloginBaseappTimer, 1.0f, false, 1.0f);
	}
}

void APtGameModeBase::StopReloginBaseappTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void APtGameModeBase::OnReloginBaseappTimer()
{
	//重登录到网关(baseapp)
	//一些移动类应用容易掉线，可以使用该功能快速的重新与服务端建立通信
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();

	if (TimerHandle.IsValid()) {
		GetWorldTimerManager().SetTimer(TimerHandle, this, &APtGameModeBase::OnReloginBaseappTimer, 1.0f, false, 3.0f);
	}
}
