/*
	Generated by KBEngine!
	Please do not modify this file!
	
	tools = kbcmd
*/

#pragma once

#include "KBECommon.h"
#include "EntityCall.h"
#include "KBETypes.h"
#include "CustomDataTypes.h"


// defined in */scripts/entity_defs/PtRoomMgr.def

namespace KBEngine
{

class KBENGINEPLUGINS_API EntityBaseEntityCall_PtRoomMgrBase : public EntityCall
{
public:

	EntityBaseEntityCall_PtRoomMgrBase(int32 eid, const FString& ename);

	virtual ~EntityBaseEntityCall_PtRoomMgrBase();
};

class KBENGINEPLUGINS_API EntityCellEntityCall_PtRoomMgrBase : public EntityCall
{
public:

	EntityCellEntityCall_PtRoomMgrBase(int32 eid, const FString& ename);

	virtual ~EntityCellEntityCall_PtRoomMgrBase();
};

}