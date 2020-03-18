/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class PtRole : public PtRoleBase)
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "Entity.h"
#include "KBETypes.h"
#include "EntityCallPtRoleBase.h"

namespace KBEngine
{

class Method;
class Property;
class MemoryStream;

// defined in */scripts/entity_defs/PtRole.def
	// Please inherit and implement "class PtRole : public PtRoleBase"
class KBENGINEPLUGINS_API PtRoleBase : public Entity
{
public:
	EntityBaseEntityCall_PtRoleBase* pBaseEntityCall;
	EntityCellEntityCall_PtRoleBase* pCellEntityCall;

	int16 BaseHP;
	virtual void onBaseHPChanged(int16 oldValue) {}
	int16 Defense;
	virtual void onDefenseChanged(int16 oldValue) {}
	int16 HP;
	virtual void onHPChanged(int16 oldValue) {}
	FString Name;
	virtual void onNameChanged(const FString& oldValue) {}
	float PowerRatio;
	virtual void onPowerRatioChanged(float oldValue) {}
	uint8 RoleType;
	virtual void onRoleTypeChanged(uint8 oldValue) {}
	FVector SpawnPoint;
	virtual void onSpawnPointChanged(const FVector& oldValue) {}
	float SpeedRatio;
	virtual void onSpeedRatioChanged(float oldValue) {}

	virtual void OnAcceptChatList(const CHAT_LIST& arg1) = 0; 
	virtual void OnAnimUpdate(const ANIM_INFO& arg1) = 0; 
	virtual void OnAttack(uint8 arg1) = 0; 
	virtual void OnIncreaseGood(uint8 arg1, const GOOD_INFO& arg2) = 0; 
	virtual void OnPassGood(uint8 arg1, const GOOD_INFO& arg2, uint8 arg3, const GOOD_INFO& arg4) = 0; 
	virtual void OnReduceGood(uint8 arg1, uint8 arg2, const GOOD_INFO& arg3) = 0; 
	virtual void OnReqBagList(const BAG_INFO& arg1, const BAG_INFO& arg2, const BAG_INFO& arg3, const BAG_INFO& arg4) = 0; 

	void onComponentsEnterworld() override;
	void onComponentsLeaveworld() override;

	void onGetBase() override;
	void onGetCell() override;
	void onLoseCell() override;

	EntityCall* getBaseEntityCall() override;
	EntityCall* getCellEntityCall() override;


	void onRemoteMethodCall(MemoryStream& stream) override;
	void onUpdatePropertys(MemoryStream& stream) override;
	void callPropertysSetMethods() override;

	PtRoleBase();
	virtual ~PtRoleBase();

	void attachComponents() override;
	void detachComponents() override;

};

}