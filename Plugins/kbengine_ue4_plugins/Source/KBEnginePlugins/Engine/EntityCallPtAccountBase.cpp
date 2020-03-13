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

void EntityBaseEntityCall_PtAccountBase::ReqCreateRole(uint8 arg1, const FString& arg2)
{
	Bundle* pBundleRet = newCall("ReqCreateRole", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint8(arg1);
	pBundleRet->writeUnicode(arg2);
	sendCall(NULL);
}

void EntityBaseEntityCall_PtAccountBase::ReqCreateRoom(const FString& arg1)
{
	Bundle* pBundleRet = newCall("ReqCreateRoom", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_PtAccountBase::ReqRemoveRole(const FString& arg1)
{
	Bundle* pBundleRet = newCall("ReqRemoveRole", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUnicode(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_PtAccountBase::ReqRoleList()
{
	Bundle* pBundleRet = newCall("ReqRoleList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_PtAccountBase::ReqRoomList()
{
	Bundle* pBundleRet = newCall("ReqRoomList", 0);
	if(!pBundleRet)
		return;

	sendCall(NULL);
}

void EntityBaseEntityCall_PtAccountBase::ReqSelectRoleGame(uint64 arg1)
{
	Bundle* pBundleRet = newCall("ReqSelectRoleGame", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}

void EntityBaseEntityCall_PtAccountBase::SelectRoomGame(uint64 arg1)
{
	Bundle* pBundleRet = newCall("SelectRoomGame", 0);
	if(!pBundleRet)
		return;

	pBundleRet->writeUint64(arg1);
	sendCall(NULL);
}



EntityCellEntityCall_PtAccountBase::EntityCellEntityCall_PtAccountBase(int32 eid, const FString& ename) : EntityCall(eid, ename)
{
	type = ENTITYCALL_TYPE_CELL;
}

EntityCellEntityCall_PtAccountBase::~EntityCellEntityCall_PtAccountBase()
{
}


}