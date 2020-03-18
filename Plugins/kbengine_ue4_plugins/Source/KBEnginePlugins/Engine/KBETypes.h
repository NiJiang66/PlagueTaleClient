/*
	Generated by KBEngine!
	Please do not modify this file!
	tools = kbcmd
*/

#pragma once

#include "KBECommon.h"

namespace KBEngine
{


// defined in */scripts/entity_defs/types.xml

typedef uint8 UINT8;

typedef uint16 UINT16;

typedef uint64 UINT64;

typedef uint32 UINT32;

typedef int8 INT8;

typedef int16 INT16;

typedef int32 INT32;

typedef int64 INT64;

typedef FString STRING;

typedef FString KBE_UNICODE;

typedef float FLOAT;

typedef double DOUBLE;

typedef TArray<uint8> PYTHON;

typedef TArray<uint8> PY_DICT;

typedef TArray<uint8> PY_TUPLE;

typedef TArray<uint8> PY_LIST;

typedef TArray<uint8> ENTITYCALL;

typedef TArray<uint8> BLOB;

typedef FVector2D VECTOR2;

typedef FVector VECTOR3;

typedef FVector4 VECTOR4;

typedef uint64 DBID;

typedef uint8 BOOL;

typedef int32 ENTITY_ID;

class KBENGINEPLUGINS_API ENTITYID_LIST : public TArray<int32>
{
public:

	ENTITYID_LIST()
	{
	}

};

typedef uint8 GOOD_TYPE;

typedef uint8 GOOD_ID;

typedef uint8 KIND_ID;

typedef uint8 BAG_TYPE;

typedef uint8 BLOCK_ID;

typedef uint8 REDUCE_RES;

class KBENGINEPLUGINS_API ROLE_DATA
{
public:
	int8 DataType;
	TArray<uint8> DataValue;

	ROLE_DATA():
	DataType(0),
	DataValue()
	{
	}

};

class KBENGINEPLUGINS_API ROLE_INFO
{
public:
	uint64 Dbid;
	FString Name;
	uint8 RoleType;
	ROLE_DATA Data;

	ROLE_INFO():
	Dbid(0),
	Name(),
	RoleType(0),
	Data()
	{
	}

};

class KBENGINEPLUGINS_API ROLE_LIST
{
public:
	TArray<ROLE_INFO> Value;

	ROLE_LIST():
	Value()
	{
	}

};

class KBENGINEPLUGINS_API ROOM_INFO
{
public:
	uint64 RoomId;
	FString Name;

	ROOM_INFO():
	RoomId(0),
	Name()
	{
	}

};

class KBENGINEPLUGINS_API ROOM_LIST
{
public:
	TArray<ROOM_INFO> Value;

	ROOM_LIST():
	Value()
	{
	}

};

class KBENGINEPLUGINS_API ANIM_INFO
{
public:
	float Speed;
	float Direction;

	ANIM_INFO():
	Speed(0.0f),
	Direction(0.0f)
	{
	}

};

class KBENGINEPLUGINS_API GOOD_INFO
{
public:
	uint8 BlockId;
	uint8 GoodId;
	uint8 Number;

	GOOD_INFO():
	BlockId(0),
	GoodId(0),
	Number(0)
	{
	}

};

class KBENGINEPLUGINS_API BAG_INFO
{
public:
	TArray<GOOD_INFO> Value;

	BAG_INFO():
	Value()
	{
	}

};

class KBENGINEPLUGINS_API SKILL_INFO
{
public:
	uint8 SkillId;
	FVector SpawnPos;
	FVector TargetPos;

	SKILL_INFO():
	SkillId(0),
	SpawnPos(),
	TargetPos()
	{
	}

};

class KBENGINEPLUGINS_API CHAT_INFO
{
public:
	uint32 Index;
	FString Name;
	FString Date;
	FString Message;

	CHAT_INFO():
	Index(0),
	Name(),
	Date(),
	Message()
	{
	}

};

class KBENGINEPLUGINS_API CHAT_LIST
{
public:
	TArray<CHAT_INFO> Value;

	CHAT_LIST():
	Value()
	{
	}

};


}