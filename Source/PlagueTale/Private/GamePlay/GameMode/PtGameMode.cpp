// Fill out your copyright notice in the Description page of Project Settings.


#include "PtGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"
#include "PtPlayerCharacter.h"
#include "PtPlayerController.h"
#include "PtRemotePlayerCharacter.h"
#include "PtEnemyCharacter.h"
#include "PTGameHUD.h"
#include "PtMainGameWidget.h"
#include "PtSkillActor.h"
#include "PtFlobActor.h"

#include "Scripts/PtEventData.h"
#include "Scripts/PtCommon.h"
#include "Scripts/PtRole.h"
#include "Scripts/PtMonster.h"
#include "Scripts/PtSkill.h"
#include "Scripts/PtFlob.h"
#include "PTGameInstance.h"



APtGameMode::APtGameMode()
{
	PlayerControllerClass = APtPlayerController::StaticClass();
	HUDClass = APtGameHUD::StaticClass();
}

void APtGameMode::InstallEvents()
{
	Super::InstallEvents();

	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterWorld, OnEnterWorld);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveWorld, OnLeaveWorld);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onEnterSpace, OnEnterSpace);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLeaveSpace, OnLeaveSpace);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_position, SetPosition);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::set_direction, SetDirection);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::updatePosition, UpdatePosition);

	KBENGINE_REGISTER_EVENT("OnAnimUpdate", OnAnimUpdate);
	KBENGINE_REGISTER_EVENT("OnAttack", OnAttack);

	KBENGINE_REGISTER_EVENT("SetBaseHP", SetBaseHP);
	KBENGINE_REGISTER_EVENT("SetHP", SetHP);
	KBENGINE_REGISTER_EVENT("SetDefense", SetDefense);
	KBENGINE_REGISTER_EVENT("SetPowerRatio", SetPowerRatio);
	KBENGINE_REGISTER_EVENT("SetSpeedRatio", SetSpeedRatio);



}

void APtGameMode::UnInstallEvents()
{
	Super::UnInstallEvents();
	if (MainGameWidget) {
		MainGameWidget->UnInstallEvents();
	}
}

void APtGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APtGameMode::OnEnterWorld(const UKBEventData* EventData)
{
	const UKBEventData_onEnterWorld* ServerData = Cast<UKBEventData_onEnterWorld>(EventData);

	//获取方向
	FRotator Direction;
	KBDir2UE4Dir(Direction, ServerData->direction);

	//根据实体id获取实体的实例，这种方法比较耗时
	KBEngine::Entity* EntityInst = *KBEngine::KBEngineApp::getSingleton().entities().Find(ServerData->entityID);

	//区分类型生成UE4对象
	if (ServerData->isPlayer) {
		//强转实体类型为PtRole
		KBEngine::PtRole* RoleInst = static_cast<KBEngine::PtRole*>(EntityInst);
		FTransform SpawnTransform(Direction, RoleInst->SpawnPoint);

		PlayerCharacter = Cast<APtPlayerCharacter>(/** 先不激活 */
			UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PlayerClassList[RoleInst->RoleType], SpawnTransform));
		if (PlayerCharacter) {
			PlayerCharacter->EntityId = ServerData->entityID;
			PlayerCharacter->RoleType = RoleInst->RoleType;
			PlayerCharacter->RoleName = RoleInst->Name;
			PlayerCharacter->MainGameMode = this;
			PlayerCharacter->IsPlayer = true;
			// 创建出角色, 需要绑定到Controller
			APtPlayerController* MainGameController = Cast<APtPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			PlayerCharacter->MainController = MainGameController;

			//设置玩家名字显示
			APtGameHUD* GameHud = Cast<APtGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
			if (GameHud) {
				GameHud->InitActorAndUI();
				if (GameHud->MainGameWidget) {
					MainGameWidget = GameHud->MainGameWidget;
					MainGameWidget->SetName(RoleInst->Name);
					MainGameWidget->PlayerCharacter = PlayerCharacter;
					PlayerCharacter->MainGameWidget = MainGameWidget;
				}
			}

			/**	激活角色Actor，并控制 */
			UGameplayStatics::FinishSpawningActor(PlayerCharacter, SpawnTransform);
			MainGameController->Possess(PlayerCharacter);
		}
	}
	else {
		// 不是玩家时，创建远程玩家、怪物、技能、掉落物、传送门等
		// 获取生成位置
		FTransform SpawnTransform(Direction, ServerData->position);

		if (ServerData->entityClassName.Equals(FString("PtRole"))) {
			//强转实体类型为PtRole
			KBEngine::PtRole* RoleInst = static_cast<KBEngine::PtRole*>(EntityInst);

			//生成远程玩家
			APtRemotePlayerCharacter* RemoteCharacter = Cast<APtRemotePlayerCharacter>(
				UGameplayStatics::BeginDeferredActorSpawnFromClass(this, RemotePlayerClassList[RoleInst->RoleType], SpawnTransform));
			if (RemoteCharacter) {	
				RemoteCharacter->EntityId = ServerData->entityID;
				RemoteCharacter->RoleType = RoleInst->RoleType;
				RemoteCharacter->RoleName = RoleInst->Name;
				RemoteCharacter->MainGameMode = this;
				RemoteCharacter->IsPlayer = false;
				UGameplayStatics::FinishSpawningActor(RemoteCharacter, SpawnTransform);
			}
		}
		else if (ServerData->entityClassName.Equals(FString("PtMonster"))) {
			//强转实体类型为PtRole
			KBEngine::PtMonster* MonsterInst = static_cast<KBEngine::PtMonster*>(EntityInst);

			//生成怪物
			APtEnemyCharacter* MonsterCharacter = Cast<APtEnemyCharacter>(
				UGameplayStatics::BeginDeferredActorSpawnFromClass(this, MonsterClassList[0], SpawnTransform));
			if (MonsterCharacter) {
				MonsterCharacter->EntityId = ServerData->entityID;
				MonsterCharacter->RoleType = MonsterInst->RoleType;
				MonsterCharacter->RoleName = MonsterInst->Name;
				MonsterCharacter->MainGameMode = this;
				MonsterCharacter->IsPlayer = false;
				UGameplayStatics::FinishSpawningActor(MonsterCharacter, SpawnTransform);
			}
		}
		else if (ServerData->entityClassName.Equals(FString("PtSkill"))) {
			//强转为PtSkill
			KBEngine::PtSkill* SkillInst = static_cast<KBEngine::PtSkill*>(EntityInst);
			//生成对象
			APtSkillActor* SkillActor = Cast<APtSkillActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, SkillClassList[SkillInst->SkillId], SpawnTransform));
			if (SkillActor) {
				SkillActor->MainGameMode = this;
				SkillActor->EntityId = ServerData->entityID;
				SkillActor->SkillId = SkillInst->SkillId;
				UGameplayStatics::FinishSpawningActor(SkillActor, SpawnTransform);
			}
		}
		else if (ServerData->entityClassName.Equals(FString("PtFlob"))) {
			//强转为PtFlob
			KBEngine::PtFlob* FlobInst = static_cast<KBEngine::PtFlob*>(EntityInst);

			//生成掉落物
			APtFlobActor* FlobActor = Cast<APtFlobActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, FlobClassList[0], SpawnTransform));
			if (FlobActor) {
				FlobActor->MainGameMode = this;
				FlobActor->EntityId = ServerData->entityID;
				FlobActor->GoodId = FlobInst->GoodId;
				UGameplayStatics::FinishSpawningActor(FlobActor, SpawnTransform);
			}
		}

	}

}

void APtGameMode::OnLeaveWorld(const UKBEventData* EventData)
{
	//玩家离开世界直接销毁这个场景, 所以这里不处理玩家离开的逻辑

	const UKBEventData_onLeaveWorld* ServerData = Cast<UKBEventData_onLeaveWorld>(EventData);
	//如果存在于OtherCharacters，说明不是本地玩家
	if (OtherCharacters.Contains(ServerData->entityID)) {
		APtBaseCharacter* BaseCharacter = *OtherCharacters.Find(ServerData->entityID);

		//根据实体Id获取实体对象
		KBEngine::Entity* EntityInst = *KBEngine::KBEngineApp::getSingleton().entities().Find(ServerData->entityID);
		//远程玩家
		if (EntityInst->className().Equals(FString("PtRole"))) {
			//直接销毁远程玩家
			BaseCharacter->Destroy();
		}
		else if (EntityInst->className().Equals(FString("PtMonster"))) {
			//敌人的话播放动画再销毁
			APtEnemyCharacter* MonsterCharacter = Cast<APtEnemyCharacter>(BaseCharacter);
			MonsterCharacter->PlayDeath();
		}
	}
	else if (SkillMap.Contains(ServerData->entityID)) {
		APtSkillActor* SkillActor = *SkillMap.Find(ServerData->entityID);
		SkillActor->PlayExplode();
	}
	else if (FlobMap.Contains(ServerData->entityID)) {
		APtFlobActor* FlobActor = *FlobMap.Find(ServerData->entityID);
		FlobActor->Destroy();
	}
}

void APtGameMode::OnEnterSpace(const UKBEventData* EventData)
{
	PtH::Debug() << "OnEnterSpace" << PtH::Endl();
}

void APtGameMode::OnLeaveSpace(const UKBEventData* EventData)
{
	//离开场景说明是进入了传送门, 在这里获取下一个房间名字保存到GameInstance
	//UPtGameInstance* GameInstance = Cast<UPtGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//GameInstance->RoomName = FText::FromString(GateActor->RoomName);
}

void APtGameMode::SetPosition(const UKBEventData* EventData)
{
	const UKBEventData_set_position* ServerData = Cast<UKBEventData_set_position>(EventData);
	if (OtherCharacters.Contains(ServerData->entityID)) {
		APtBaseCharacter* CharacterEntity = *OtherCharacters.Find(ServerData->entityID);
		//因为只有首次进入世界才会调用到这个函数，所以直接设置ActorLocation
		CharacterEntity->SetActorLocation(ServerData->position);
		CharacterEntity->SetTargetPosition(ServerData->position);
	}
	if (SkillMap.Contains(ServerData->entityID)) {
		APtSkillActor* SkillActor = *SkillMap.Find(ServerData->entityID);
		SkillActor->SetActorLocation(ServerData->position);
		SkillActor->SetTargetPosition(ServerData->position);
	}
	if (FlobMap.Contains(ServerData->entityID)) {
		APtFlobActor* FlobActor = *FlobMap.Find(ServerData->entityID);
		FlobActor->SetActorLocation(ServerData->position);
		FlobActor->SetTargetPosition(ServerData->position);
	}
}

void APtGameMode::SetDirection(const UKBEventData* EventData)
{
	const UKBEventData_set_direction* ServerData = Cast<UKBEventData_set_direction>(EventData);
	if (OtherCharacters.Contains(ServerData->entityID)) {
		APtBaseCharacter* CharacterEntity = *OtherCharacters.Find(ServerData->entityID);
		//因为只有首次进入世界才会调用到这个函数，所以直接设置ActorRotation
		CharacterEntity->SetActorRotation(ServerData->direction);
		CharacterEntity->SetTargetRotator(ServerData->direction);
	}	
	if (SkillMap.Contains(ServerData->entityID)) {
		APtSkillActor* SkillActor = *SkillMap.Find(ServerData->entityID);
		SkillActor->SetActorRotation(ServerData->direction);
	}
	if (FlobMap.Contains(ServerData->entityID)) {
		APtFlobActor* FlobActor = *FlobMap.Find(ServerData->entityID);
		FlobActor->SetActorRotation(ServerData->direction);
	}
}

void APtGameMode::UpdatePosition(const UKBEventData* EventData)
{
	const UKBEventData_updatePosition* ServerData = Cast<UKBEventData_updatePosition>(EventData);
	if (OtherCharacters.Contains(ServerData->entityID)) {
		APtBaseCharacter* CharacterEntity = *OtherCharacters.Find(ServerData->entityID);
		CharacterEntity->SetTargetPosition(ServerData->position);
		CharacterEntity->SetTargetRotator(ServerData->direction);
	}
	if (SkillMap.Contains(ServerData->entityID)) {
		APtSkillActor* SkillActor = *SkillMap.Find(ServerData->entityID);
		SkillActor->SetTargetPosition(ServerData->position);
	}
	if (FlobMap.Contains(ServerData->entityID)) {
		APtFlobActor* FlobActor = *FlobMap.Find(ServerData->entityID);
		FlobActor->SetTargetPosition(ServerData->position);
	}
}

void APtGameMode::OnAnimUpdate(const UKBEventData* EventData)
{
	const UKBEventData_OnAnimUpdate* ServerData = Cast<UKBEventData_OnAnimUpdate>(EventData);
	if (OtherCharacters.Contains(ServerData->EntityId)) {
		APtBaseCharacter* CharacterEntity = *OtherCharacters.Find(ServerData->EntityId);
		CharacterEntity->SetTargetAnim(ServerData->Speed, ServerData->Direction);
	}
}

void APtGameMode::SetBaseHP(const UKBEventData* EventData)
{
	const UKBEventData_SetBaseHP* ServerData = Cast<UKBEventData_SetBaseHP>(EventData);
	if (ServerData->IsPlayer) {
		if (PlayerCharacter) {
			PlayerCharacter->SetBaseHP(ServerData->BaseHP);
			float HPPercent = FMath::Clamp((float)PlayerCharacter->HP / (float)PlayerCharacter->BaseHP, 0.f, 1.f);
			if (MainGameWidget) {
				MainGameWidget->SetHPPercent(HPPercent);
				//还要更新血值上限到UI
				MainGameWidget->SetBaseHP(ServerData->BaseHP);
			}
		}
	}
	else {
		if (OtherCharacters.Contains(ServerData->EntityId)) {
			APtBaseCharacter* CharacterEntity = *OtherCharacters.Find(ServerData->EntityId);
			CharacterEntity->SetBaseHP(ServerData->BaseHP);
		}
	}
}

void APtGameMode::SetHP(const UKBEventData* EventData)
{
	const UKBEventData_SetHP* ServerData = Cast<UKBEventData_SetHP>(EventData);
	if (ServerData->IsPlayer) {
		if (PlayerCharacter) {
			PlayerCharacter->SetHP(ServerData->HP);

			//计算血值百分比
			float HPPercent = FMath::Clamp(((float)PlayerCharacter->HP / (float)PlayerCharacter->BaseHP), 0.f, 1.f);
			if (MainGameWidget) {
				MainGameWidget->SetHPPercent(HPPercent);
			}			
		}
	}
	else {
		if (OtherCharacters.Contains(ServerData->EntityId)) {
			APtBaseCharacter* CharacterEntity = *OtherCharacters.Find(ServerData->EntityId);
			CharacterEntity->SetHP(ServerData->HP);
		}
	}
}

void APtGameMode::SetDefense(const UKBEventData* EventData)
{
	//防御值只有玩家会更新, 防御力只更新UI显示
	const UKBEventData_SetDefense* ServerData = Cast<UKBEventData_SetDefense>(EventData);

	if (MainGameWidget) {
		MainGameWidget->SetDefense(ServerData->Defense);
	}		
}

void APtGameMode::SetPowerRatio(const UKBEventData* EventData)
{
	//力量加成只有玩家会更新, 力量加成只更新UI显示
	const UKBEventData_SetPowerRatio* ServerData = Cast<UKBEventData_SetPowerRatio>(EventData);

	if (MainGameWidget) {
		MainGameWidget->SetPowerRatio(ServerData->PowerRatio);
	}
}

void APtGameMode::SetSpeedRatio(const UKBEventData* EventData)
{
	//速度加成只有玩家会更新
	const UKBEventData_SetSpeedRatio* ServerData = Cast<UKBEventData_SetSpeedRatio>(EventData);

	//更新到玩家
	if (PlayerCharacter) {
		PlayerCharacter->SetSpeedRatio(ServerData->SpeedRatio);
	}
	//更新到UI
	if (MainGameWidget) {
		MainGameWidget->SetSpeedRatio(ServerData->SpeedRatio);
	}
}

void APtGameMode::OnAttack(const UKBEventData* EventData)
{
	const UKBEventData_OnAttack* ServerData = Cast<UKBEventData_OnAttack>(EventData);
	//如果是玩家
	if (ServerData->EntityId == PlayerCharacter->EntityId) {
		PlayerCharacter->OnAttack(ServerData->SkillId);
	}
	//如果是其他角色（怪物或远程玩家角色）
	else if (OtherCharacters.Contains(ServerData->EntityId)) {
		APtBaseCharacter* CharacterEntity = *OtherCharacters.Find(ServerData->EntityId);
		CharacterEntity->OnAttack(ServerData->SkillId);
	}
}


void APtGameMode::OnLeaveRoom(const UKBEventData* EventData)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("RoleMap"));
}

void APtGameMode::AddSpaceGeometryMapping(const UKBEventData* EventData)
{
	const UKBEventData_addSpaceGeometryMapping* ServerData = Cast<UKBEventData_addSpaceGeometryMapping>(EventData);

	FString MapName;
	FString TempStr;
	ServerData->spaceResPath.Split("/", &TempStr, &MapName);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
}