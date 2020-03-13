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

	FString Name;
	virtual void onNameChanged(const FString& oldValue) {}
	uint8 RoleType;
	virtual void onRoleTypeChanged(uint8 oldValue) {}


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