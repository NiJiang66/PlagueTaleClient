#include "EntityCallPtAccountBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_PtAccountBase::EntityBaseEntityCall_PtAccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_PtAccountBase::~EntityBaseEntityCall_PtAccountBase()
{
}



EntityCellEntityCall_PtAccountBase::EntityCellEntityCall_PtAccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_PtAccountBase::~EntityCellEntityCall_PtAccountBase()
{
}


}