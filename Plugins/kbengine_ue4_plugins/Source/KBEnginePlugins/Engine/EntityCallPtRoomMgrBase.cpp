#include "EntityCallPtRoomMgrBase.h"
#include "Bundle.h"

namespace KBEngine
{

EntityBaseEntityCall_PtRoomMgrBase::EntityBaseEntityCall_PtRoomMgrBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_BASE;
}

EntityBaseEntityCall_PtRoomMgrBase::~EntityBaseEntityCall_PtRoomMgrBase()
{
}



EntityCellEntityCall_PtRoomMgrBase::EntityCellEntityCall_PtRoomMgrBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_PtRoomMgrBase::~EntityCellEntityCall_PtRoomMgrBase()
{
}


}