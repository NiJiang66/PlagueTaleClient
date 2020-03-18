#include "EntityCallPtRoleBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_PtRoleBase::EntityBaseEntityCall_PtRoleBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_PtRoleBase::~EntityBaseEntityCall_PtRoleBase()
{
}

void EntityBaseEntityCall_PtRoleBase::PassGood(uint8 arg1, uint8 arg2, uint8 arg3, uint8 arg4)
{
	Bundle* pBundleRet = newCall("PassGood", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	pBundleRet->writeUint8(arg2);
	pBundleRet->writeUint8(arg3);
	pBundleRet->writeUint8(arg4);
	sendCall(NULL);
}

void EntityBaseEntityCall_PtRoleBase::ReduceGood(uint8 arg1, uint8 arg2)
{
	Bundle* pBundleRet = newCall("ReduceGood", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	pBundleRet->writeUint8(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_PtRoleBase::ReqBagList()
{
	Bundle* pBundleRet = newCall("ReqBagList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}



EntityCellEntityCall_PtRoleBase::EntityCellEntityCall_PtRoleBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_PtRoleBase::~EntityCellEntityCall_PtRoleBase()
{
}

void EntityCellEntityCall_PtRoleBase::AnimUpdate(const ANIM_INFO& arg1)
{
	Bundle* pBundleRet = newCall("AnimUpdate", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_ANIM_INFO*)EntityDef::id2datatypes[30])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_PtRoleBase::Attack(const SKILL_INFO& arg1)
{
	Bundle* pBundleRet = newCall("Attack", 0);
	if(!pBundleRet)
		return;

	((DATATYPE_SKILL_INFO*)EntityDef::id2datatypes[34])->addToStreamEx(*pBundleRet, arg1);
	sendCall(NULL);
}

void EntityCellEntityCall_PtRoleBase::Relive()
{
	Bundle* pBundleRet = newCall("Relive", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}


}