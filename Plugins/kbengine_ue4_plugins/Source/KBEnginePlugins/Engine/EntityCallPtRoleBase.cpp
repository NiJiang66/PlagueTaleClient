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

void EntityCellEntityCall_PtRoleBase::Attack()
{
	Bundle* pBundleRet = newCall("Attack", 0);
	if(!pBundleRet)
		return;

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