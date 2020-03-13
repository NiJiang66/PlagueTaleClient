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


}