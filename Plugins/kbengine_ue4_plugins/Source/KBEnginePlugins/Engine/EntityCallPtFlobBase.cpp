#include "EntityCallPtFlobBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_PtFlobBase::EntityBaseEntityCall_PtFlobBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_PtFlobBase::~EntityBaseEntityCall_PtFlobBase()
{
}



EntityCellEntityCall_PtFlobBase::EntityCellEntityCall_PtFlobBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_PtFlobBase::~EntityCellEntityCall_PtFlobBase()
{
}


}