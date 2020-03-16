#include "EntityCallPtSkillBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_PtSkillBase::EntityBaseEntityCall_PtSkillBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_PtSkillBase::~EntityBaseEntityCall_PtSkillBase()
{
}



EntityCellEntityCall_PtSkillBase::EntityCellEntityCall_PtSkillBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_PtSkillBase::~EntityCellEntityCall_PtSkillBase()
{
}


}