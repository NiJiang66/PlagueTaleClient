// Fill out your copyright notice in the Description page of Project Settings.


#include "PtStartGameMode.h"
#include "PtStartHUD.h"
#include "PtStartController.h"
#include "PtKBEClient.h"

#include "Scripts/PtCommon.h"
#include "Engine/KBEngine.h"
#include "Engine/KBEMain.h"

APtStartGameMode::APtStartGameMode()
{
	PlayerControllerClass = APtStartController::StaticClass();
	HUDClass = APtStartHUD::StaticClass();
}

void APtStartGameMode::InstallEvents()
{
	Super::InstallEvents();

	// login
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);
	KBENGINE_REGISTER_EVENT("Loginapp_importClientMessages", Loginapp_importClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientMessages", Baseapp_importClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientEntityDef", Baseapp_importClientEntityDef);
}

void APtStartGameMode::OnCreateAccountResult(const UKBEventData* pEventData)
{
	const UKBEventData_onCreateAccountResult* ServerData = Cast<UKBEventData_onCreateAccountResult>(pEventData);

	PtH::Debug() << "OnCreateAccountResult : errorCode --> " << ServerData->errorCode << " ; errorStr --> " << ServerData->errorStr << PtH::Endl();
}

void APtStartGameMode::OnLoginFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginFailed* ServerData = Cast<UKBEventData_onLoginFailed>(pEventData);

	PtH::Debug() << "OnLoginFailed : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << PtH::Endl();
}

void APtStartGameMode::OnVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onVersionNotMatch* ServerData = Cast<UKBEventData_onVersionNotMatch>(pEventData);

	PtH::Debug() << "OnVersionNotMatch : clientVersion --> " << ServerData->clientVersion << " ; serverVersion --> " << ServerData->serverVersion << PtH::Endl();
}

void APtStartGameMode::OnScriptVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onScriptVersionNotMatch* ServerData = Cast<UKBEventData_onScriptVersionNotMatch>(pEventData);

	PtH::Debug() << "OnScriptVersionNotMatch : clientScriptVersion --> " << ServerData->clientScriptVersion << " ; serverScriptVersion --> " << PtH::Endl();
}

void APtStartGameMode::OnLoginBaseappFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseappFailed* ServerData = Cast<UKBEventData_onLoginBaseappFailed>(pEventData);

	PtH::Debug() << "OnLoginBaseappFailed : failedcode --> " << ServerData->failedcode << " ; errorStr --> " << ServerData->errorStr << PtH::Endl();
}

void APtStartGameMode::OnLoginSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginSuccessfully* ServerData = Cast<UKBEventData_onLoginSuccessfully>(pEventData);

	PtH::Debug() << "OnLoginSuccessfully : entity_uuid --> " << ServerData->entity_uuid << " ; entity_id --> " << ServerData->entity_id << PtH::Endl();
	
	//登录成功之后打开角色选择关卡
	UGameplayStatics::OpenLevel(GetWorld(), FName("RoleMap"));
}

void APtStartGameMode::OnLoginBaseapp(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseapp* ServerData = Cast<UKBEventData_onLoginBaseapp>(pEventData);

	PtH::Debug() << "OnLoginBaseapp : eventName --> " << ServerData->eventName << PtH::Endl();
}

void APtStartGameMode::Loginapp_importClientMessages(const UKBEventData* pEventData)
{
	const UKBEventData_Loginapp_importClientMessages* ServerData = Cast<UKBEventData_Loginapp_importClientMessages>(pEventData);

	PtH::Debug() << "Loginapp_importClientMessages : eventName --> " << ServerData->eventName << PtH::Endl();
}

void APtStartGameMode::Baseapp_importClientMessages(const UKBEventData* pEventData)
{
	const UKBEventData_Baseapp_importClientMessages* ServerData = Cast<UKBEventData_Baseapp_importClientMessages>(pEventData);

	PtH::Debug() << "Baseapp_importClientMessages : eventName --> " << ServerData->eventName << PtH::Endl();
}

void APtStartGameMode::Baseapp_importClientEntityDef(const UKBEventData* pEventData)
{
	const UKBEventData_Baseapp_importClientEntityDef* ServerData = Cast<UKBEventData_Baseapp_importClientEntityDef>(pEventData);

	PtH::Debug() << "Baseapp_importClientEntityDef : eventName --> " << ServerData->eventName << PtH::Endl();
}

void APtStartGameMode::BeginPlay()
{
	//每次进入到登录界面时先清理一次KBE，否则KBE插件内缓存的内容将一直存在
	KBEngine::KBEngineApp::getSingleton().reset();

	Super::BeginPlay();

	for (TActorIterator<APtKBEClient> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		KBEMain = (*ActorItr)->KBEMain;
	}

}

