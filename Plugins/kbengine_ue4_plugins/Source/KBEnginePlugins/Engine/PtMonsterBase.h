/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class PtMonster : public PtMonsterBase)
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "Entity.h"
#include "KBETypes.h"
#include "EntityCallPtMonsterBase.h"

namespace KBEngine
{

class Method;
class Property;
class MemoryStream;

// defined in */scripts/entity_defs/PtMonster.def
	// Please inherit and implement "class PtMonster : public PtMonsterBase"
class KBENGINEPLUGINS_API PtMonsterBase : public Entity
{
public:
	EntityBaseEntityCall_PtMonsterBase* pBaseEntityCall;
	EntityCellEntityCall_PtMonsterBase* pCellEntityCall;

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
	float SpeedRatio;
	virtual void onSpeedRatioChanged(float oldValue) {}

	virtual void OnAnimUpdate(const ANIM_INFO& arg1) = 0; 

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

	PtMonsterBase();
	virtual ~PtMonsterBase();

	void attachComponents() override;
	void detachComponents() override;

};

}