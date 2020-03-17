// Fill out your copyright notice in the Description page of Project Settings.


#include "PtGameHUD.h"
#include "PtMainGameWidget.h"
#include "PTGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"

void APtGameHUD::BeginPlay()
{
	Super::BeginPlay();
	InitActorAndUI();
}

void APtGameHUD::InitActorAndUI()
{
	if (MainGameWidget == nullptr) {
		MainGameWidget = CreateWidget<UPtMainGameWidget>(GetWorld(), RoleWidgetClass);
		if (MainGameWidget) {
			MainGameWidget->AddToViewport();
			//注册KBE事件以及设置房间名
			UPtGameInstance* GameInstance = Cast<UPtGameInstance>(UGameplayStatics::GetGameInstance(this));
			MainGameWidget->InstallEvents(GameInstance->RoomName);
		}

		check(KBEngine::KBEngineApp::getSingleton().isInitialized());
		// 如果已经有被创建的实体，说明他们在上一个场景未来得及跳转之前已经通知创建了，
		// 但由于我们的world场景并没有来得及创建，这部分实体进入世界事件已经漏掉	
		// 此时我们需要再次触发一次onEnterWorld，让表现层能够在游戏场景中创建出所有的实体，否则可能只有部分实体创建出来
		KBEngine::KBEngineApp::ENTITIES_MAP& EntitiesMap = KBEngine::KBEngineApp::getSingleton().entities();
		for (auto& EntityItem : EntitiesMap) {
			KBEngine::Entity* EntityInst = EntityItem.Value;

			UKBEventData_onEnterWorld* EventData = NewObject<UKBEventData_onEnterWorld>();
			EventData->entityID = EntityInst->id();
			EventData->spaceID = KBEngine::KBEngineApp::getSingleton().spaceID();
			KBPos2UE4Pos(EventData->position, EntityInst->position);
			EventData->direction = EntityInst->direction;
			EventData->moveSpeed = EntityInst->velocity();
			EventData->isOnGround = EntityInst->isOnGround();
			EventData->isPlayer = EntityInst->isPlayer();
			EventData->entityClassName = EntityInst->className();
			EventData->res = TEXT("");
			KBENGINE_EVENT_FIRE(KBEngine::KBEventTypes::onEnterWorld, EventData);
		}

		//在角色和UI都创建出来后, 向服务器请求背包数据
		KBENGINE_EVENT_FIRE("ReqBagList", NewObject<UKBEventData>());
	}
}
