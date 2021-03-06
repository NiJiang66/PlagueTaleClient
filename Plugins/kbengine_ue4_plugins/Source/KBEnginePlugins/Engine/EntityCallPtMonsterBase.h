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


// defined in */scripts/entity_defs/PtMonster.def

namespace KBEngine
{

class KBENGINEPLUGINS_API EntityBaseEntityCall_PtMonsterBase : public EntityCall
{
public:

	EntityBaseEntityCall_PtMonsterBase(int32 eid, const FString& ename);

	virtual ~EntityBaseEntityCall_PtMonsterBase();
};

class KBENGINEPLUGINS_API EntityCellEntityCall_PtMonsterBase : public EntityCall
{
public:

	EntityCellEntityCall_PtMonsterBase(int32 eid, const FString& ename);

	virtual ~EntityCellEntityCall_PtMonsterBase();
	void AnimUpdate(const ANIM_INFO& arg1);
	void Attack(const SKILL_INFO& arg1);
	void Relive();
};

}