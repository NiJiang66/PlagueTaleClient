#include "EntityCallPtRoomBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_PtRoomBase::EntityBaseEntityCall_PtRoomBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_PtRoomBase::~EntityBaseEntityCall_PtRoomBase()
{
}



EntityCellEntityCall_PtRoomBase::EntityCellEntityCall_PtRoomBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_PtRoomBase::~EntityCellEntityCall_PtRoomBase()
{
}


}