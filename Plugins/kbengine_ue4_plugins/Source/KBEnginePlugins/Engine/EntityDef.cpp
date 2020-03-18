#include "EntityDef.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "KBVar.h"
#include "Entity.h"

#include "Scripts/PtAccount.h"
#include "Scripts/PtRole.h"
#include "Scripts/PtMonster.h"
#include "Scripts/PtFlob.h"
#include "Scripts/PtSkill.h"

namespace KBEngine
{

TMap<FString, uint16> EntityDef::datatype2id;
TMap<FString, DATATYPE_BASE*> EntityDef::datatypes;
TMap<uint16, DATATYPE_BASE*> EntityDef::id2datatypes;
TMap<FString, int32> EntityDef::entityclass;
TMap<FString, ScriptModule*> EntityDef::moduledefs;
TMap<uint16, ScriptModule*> EntityDef::idmoduledefs;

bool EntityDef::initialize()
{
	initDataTypes();
	initDefTypes();
	initScriptModules();
	return true;
}

bool EntityDef::reset()
{
	clear();
	return initialize();
}

void EntityDef::clear()
{
	TArray<DATATYPE_BASE*> deleted_datatypes;
	for (auto& item : EntityDef::datatypes)
	{
		int32 idx = deleted_datatypes.Find(item.Value);
		if (idx != INDEX_NONE)
			continue;

		deleted_datatypes.Add(item.Value);
		delete item.Value;
	}

	for (auto& item : EntityDef::moduledefs)
		delete item.Value;

	datatype2id.Empty();
	datatypes.Empty();
	id2datatypes.Empty();
	entityclass.Empty();
	moduledefs.Empty();
	idmoduledefs.Empty();
}

void EntityDef::initDataTypes()
{
	datatypes.Add(TEXT("UINT8"), new DATATYPE_UINT8());
	datatypes.Add(TEXT("UINT16"), new DATATYPE_UINT16());
	datatypes.Add(TEXT("UINT32"), new DATATYPE_UINT32());
	datatypes.Add(TEXT("UINT64"), new DATATYPE_UINT64());

	datatypes.Add(TEXT("INT8"), new DATATYPE_INT8());
	datatypes.Add(TEXT("INT16"), new DATATYPE_INT16());
	datatypes.Add(TEXT("INT32"), new DATATYPE_INT32());
	datatypes.Add(TEXT("INT64"), new DATATYPE_INT64());

	datatypes.Add(TEXT("FLOAT"), new DATATYPE_FLOAT());
	datatypes.Add(TEXT("DOUBLE"), new DATATYPE_DOUBLE());

	datatypes.Add(TEXT("STRING"), new DATATYPE_STRING());
	datatypes.Add(TEXT("VECTOR2"), new DATATYPE_VECTOR2());

	datatypes.Add(TEXT("VECTOR3"), new DATATYPE_VECTOR3());

	datatypes.Add(TEXT("VECTOR4"), new DATATYPE_VECTOR4());
	datatypes.Add(TEXT("PYTHON"), new DATATYPE_PYTHON());

	datatypes.Add(TEXT("UNICODE"), new DATATYPE_UNICODE());
	datatypes.Add(TEXT("ENTITYCALL"), new DATATYPE_ENTITYCALL());

	datatypes.Add(TEXT("BLOB"), new DATATYPE_BLOB());
}

Entity* EntityDef::createEntity(int utype)
{
	Entity* pEntity = NULL;

	switch(utype)
	{
		case 1:
			pEntity = new PtAccount();
			break;
		case 2:
			pEntity = new PtRole();
			break;
		case 5:
			pEntity = new PtMonster();
			break;
		case 6:
			pEntity = new PtFlob();
			break;
		case 7:
			pEntity = new PtSkill();
			break;
		default:
			SCREEN_ERROR_MSG("EntityDef::createEntity() : entity(%d) not found!", utype);
			break;
	};

	return pEntity;
}

void EntityDef::initScriptModules()
{
	ScriptModule* pPtAccountModule = new ScriptModule("PtAccount", 1);
	EntityDef::moduledefs.Add(TEXT("PtAccount"), pPtAccountModule);
	EntityDef::idmoduledefs.Add(1, pPtAccountModule);

	Property* pPtAccount_position = new Property();
	pPtAccount_position->name = TEXT("position");
	pPtAccount_position->properUtype = 40000;
	pPtAccount_position->properFlags = 4;
	pPtAccount_position->aliasID = 1;
	KBVar* pPtAccount_position_defval = new KBVar(FVector());
	pPtAccount_position->pDefaultVal = pPtAccount_position_defval;
	pPtAccountModule->propertys.Add(TEXT("position"), pPtAccount_position); 

	pPtAccountModule->usePropertyDescrAlias = true;
	pPtAccountModule->idpropertys.Add((uint16)pPtAccount_position->aliasID, pPtAccount_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), property(position / 40000).");

	Property* pPtAccount_direction = new Property();
	pPtAccount_direction->name = TEXT("direction");
	pPtAccount_direction->properUtype = 40001;
	pPtAccount_direction->properFlags = 4;
	pPtAccount_direction->aliasID = 2;
	KBVar* pPtAccount_direction_defval = new KBVar(FVector());
	pPtAccount_direction->pDefaultVal = pPtAccount_direction_defval;
	pPtAccountModule->propertys.Add(TEXT("direction"), pPtAccount_direction); 

	pPtAccountModule->usePropertyDescrAlias = true;
	pPtAccountModule->idpropertys.Add((uint16)pPtAccount_direction->aliasID, pPtAccount_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), property(direction / 40001).");

	Property* pPtAccount_spaceID = new Property();
	pPtAccount_spaceID->name = TEXT("spaceID");
	pPtAccount_spaceID->properUtype = 40002;
	pPtAccount_spaceID->properFlags = 16;
	pPtAccount_spaceID->aliasID = 3;
	KBVar* pPtAccount_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pPtAccount_spaceID->pDefaultVal = pPtAccount_spaceID_defval;
	pPtAccountModule->propertys.Add(TEXT("spaceID"), pPtAccount_spaceID); 

	pPtAccountModule->usePropertyDescrAlias = true;
	pPtAccountModule->idpropertys.Add((uint16)pPtAccount_spaceID->aliasID, pPtAccount_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), property(spaceID / 40002).");

	Property* pPtAccount_LastSelRole = new Property();
	pPtAccount_LastSelRole->name = TEXT("LastSelRole");
	pPtAccount_LastSelRole->properUtype = 2;
	pPtAccount_LastSelRole->properFlags = 32;
	pPtAccount_LastSelRole->aliasID = 4;
	KBVar* pPtAccount_LastSelRole_defval = new KBVar((uint64)FCString::Atoi64(TEXT("0")));
	pPtAccount_LastSelRole->pDefaultVal = pPtAccount_LastSelRole_defval;
	pPtAccountModule->propertys.Add(TEXT("LastSelRole"), pPtAccount_LastSelRole); 

	pPtAccountModule->usePropertyDescrAlias = true;
	pPtAccountModule->idpropertys.Add((uint16)pPtAccount_LastSelRole->aliasID, pPtAccount_LastSelRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), property(LastSelRole / 2).");

	TArray<DATATYPE_BASE*> PtAccount_OnCreateRoleResult_args;
	PtAccount_OnCreateRoleResult_args.Add(EntityDef::id2datatypes[2]);
	PtAccount_OnCreateRoleResult_args.Add(EntityDef::id2datatypes[24]);

	Method* pPtAccount_OnCreateRoleResult = new Method();
	pPtAccount_OnCreateRoleResult->name = TEXT("OnCreateRoleResult");
	pPtAccount_OnCreateRoleResult->methodUtype = 9;
	pPtAccount_OnCreateRoleResult->aliasID = 1;
	pPtAccount_OnCreateRoleResult->args = PtAccount_OnCreateRoleResult_args;

	pPtAccountModule->methods.Add(TEXT("OnCreateRoleResult"), pPtAccount_OnCreateRoleResult); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnCreateRoleResult->aliasID, pPtAccount_OnCreateRoleResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnCreateRoleResult / 9).");

	TArray<DATATYPE_BASE*> PtAccount_OnCreateRoom_args;
	PtAccount_OnCreateRoom_args.Add(EntityDef::id2datatypes[2]);
	PtAccount_OnCreateRoom_args.Add(EntityDef::id2datatypes[27]);

	Method* pPtAccount_OnCreateRoom = new Method();
	pPtAccount_OnCreateRoom->name = TEXT("OnCreateRoom");
	pPtAccount_OnCreateRoom->methodUtype = 13;
	pPtAccount_OnCreateRoom->aliasID = 2;
	pPtAccount_OnCreateRoom->args = PtAccount_OnCreateRoom_args;

	pPtAccountModule->methods.Add(TEXT("OnCreateRoom"), pPtAccount_OnCreateRoom); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnCreateRoom->aliasID, pPtAccount_OnCreateRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnCreateRoom / 13).");

	TArray<DATATYPE_BASE*> PtAccount_OnRemoveRole_args;
	PtAccount_OnRemoveRole_args.Add(EntityDef::id2datatypes[5]);

	Method* pPtAccount_OnRemoveRole = new Method();
	pPtAccount_OnRemoveRole->name = TEXT("OnRemoveRole");
	pPtAccount_OnRemoveRole->methodUtype = 10;
	pPtAccount_OnRemoveRole->aliasID = 3;
	pPtAccount_OnRemoveRole->args = PtAccount_OnRemoveRole_args;

	pPtAccountModule->methods.Add(TEXT("OnRemoveRole"), pPtAccount_OnRemoveRole); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnRemoveRole->aliasID, pPtAccount_OnRemoveRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnRemoveRole / 10).");

	TArray<DATATYPE_BASE*> PtAccount_OnReqRoleList_args;
	PtAccount_OnReqRoleList_args.Add(EntityDef::id2datatypes[25]);

	Method* pPtAccount_OnReqRoleList = new Method();
	pPtAccount_OnReqRoleList->name = TEXT("OnReqRoleList");
	pPtAccount_OnReqRoleList->methodUtype = 8;
	pPtAccount_OnReqRoleList->aliasID = 4;
	pPtAccount_OnReqRoleList->args = PtAccount_OnReqRoleList_args;

	pPtAccountModule->methods.Add(TEXT("OnReqRoleList"), pPtAccount_OnReqRoleList); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnReqRoleList->aliasID, pPtAccount_OnReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnReqRoleList / 8).");

	TArray<DATATYPE_BASE*> PtAccount_OnReqRoomList_args;
	PtAccount_OnReqRoomList_args.Add(EntityDef::id2datatypes[28]);

	Method* pPtAccount_OnReqRoomList = new Method();
	pPtAccount_OnReqRoomList->name = TEXT("OnReqRoomList");
	pPtAccount_OnReqRoomList->methodUtype = 12;
	pPtAccount_OnReqRoomList->aliasID = 5;
	pPtAccount_OnReqRoomList->args = PtAccount_OnReqRoomList_args;

	pPtAccountModule->methods.Add(TEXT("OnReqRoomList"), pPtAccount_OnReqRoomList); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnReqRoomList->aliasID, pPtAccount_OnReqRoomList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnReqRoomList / 12).");

	TArray<DATATYPE_BASE*> PtAccount_OnSelectRoleGame_args;
	PtAccount_OnSelectRoleGame_args.Add(EntityDef::id2datatypes[2]);
	PtAccount_OnSelectRoleGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pPtAccount_OnSelectRoleGame = new Method();
	pPtAccount_OnSelectRoleGame->name = TEXT("OnSelectRoleGame");
	pPtAccount_OnSelectRoleGame->methodUtype = 11;
	pPtAccount_OnSelectRoleGame->aliasID = 6;
	pPtAccount_OnSelectRoleGame->args = PtAccount_OnSelectRoleGame_args;

	pPtAccountModule->methods.Add(TEXT("OnSelectRoleGame"), pPtAccount_OnSelectRoleGame); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnSelectRoleGame->aliasID, pPtAccount_OnSelectRoleGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnSelectRoleGame / 11).");

	TArray<DATATYPE_BASE*> PtAccount_ReqCreateRole_args;
	PtAccount_ReqCreateRole_args.Add(EntityDef::id2datatypes[2]);
	PtAccount_ReqCreateRole_args.Add(EntityDef::id2datatypes[12]);

	Method* pPtAccount_ReqCreateRole = new Method();
	pPtAccount_ReqCreateRole->name = TEXT("ReqCreateRole");
	pPtAccount_ReqCreateRole->methodUtype = 2;
	pPtAccount_ReqCreateRole->aliasID = -1;
	pPtAccount_ReqCreateRole->args = PtAccount_ReqCreateRole_args;

	pPtAccountModule->methods.Add(TEXT("ReqCreateRole"), pPtAccount_ReqCreateRole); 
	pPtAccountModule->base_methods.Add(TEXT("ReqCreateRole"), pPtAccount_ReqCreateRole);

	pPtAccountModule->idbase_methods.Add(pPtAccount_ReqCreateRole->methodUtype, pPtAccount_ReqCreateRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(ReqCreateRole / 2).");

	TArray<DATATYPE_BASE*> PtAccount_ReqCreateRoom_args;
	PtAccount_ReqCreateRoom_args.Add(EntityDef::id2datatypes[12]);

	Method* pPtAccount_ReqCreateRoom = new Method();
	pPtAccount_ReqCreateRoom->name = TEXT("ReqCreateRoom");
	pPtAccount_ReqCreateRoom->methodUtype = 6;
	pPtAccount_ReqCreateRoom->aliasID = -1;
	pPtAccount_ReqCreateRoom->args = PtAccount_ReqCreateRoom_args;

	pPtAccountModule->methods.Add(TEXT("ReqCreateRoom"), pPtAccount_ReqCreateRoom); 
	pPtAccountModule->base_methods.Add(TEXT("ReqCreateRoom"), pPtAccount_ReqCreateRoom);

	pPtAccountModule->idbase_methods.Add(pPtAccount_ReqCreateRoom->methodUtype, pPtAccount_ReqCreateRoom);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(ReqCreateRoom / 6).");

	TArray<DATATYPE_BASE*> PtAccount_ReqRemoveRole_args;
	PtAccount_ReqRemoveRole_args.Add(EntityDef::id2datatypes[12]);

	Method* pPtAccount_ReqRemoveRole = new Method();
	pPtAccount_ReqRemoveRole->name = TEXT("ReqRemoveRole");
	pPtAccount_ReqRemoveRole->methodUtype = 3;
	pPtAccount_ReqRemoveRole->aliasID = -1;
	pPtAccount_ReqRemoveRole->args = PtAccount_ReqRemoveRole_args;

	pPtAccountModule->methods.Add(TEXT("ReqRemoveRole"), pPtAccount_ReqRemoveRole); 
	pPtAccountModule->base_methods.Add(TEXT("ReqRemoveRole"), pPtAccount_ReqRemoveRole);

	pPtAccountModule->idbase_methods.Add(pPtAccount_ReqRemoveRole->methodUtype, pPtAccount_ReqRemoveRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(ReqRemoveRole / 3).");

	TArray<DATATYPE_BASE*> PtAccount_ReqRoleList_args;

	Method* pPtAccount_ReqRoleList = new Method();
	pPtAccount_ReqRoleList->name = TEXT("ReqRoleList");
	pPtAccount_ReqRoleList->methodUtype = 1;
	pPtAccount_ReqRoleList->aliasID = -1;
	pPtAccount_ReqRoleList->args = PtAccount_ReqRoleList_args;

	pPtAccountModule->methods.Add(TEXT("ReqRoleList"), pPtAccount_ReqRoleList); 
	pPtAccountModule->base_methods.Add(TEXT("ReqRoleList"), pPtAccount_ReqRoleList);

	pPtAccountModule->idbase_methods.Add(pPtAccount_ReqRoleList->methodUtype, pPtAccount_ReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(ReqRoleList / 1).");

	TArray<DATATYPE_BASE*> PtAccount_ReqRoomList_args;

	Method* pPtAccount_ReqRoomList = new Method();
	pPtAccount_ReqRoomList->name = TEXT("ReqRoomList");
	pPtAccount_ReqRoomList->methodUtype = 5;
	pPtAccount_ReqRoomList->aliasID = -1;
	pPtAccount_ReqRoomList->args = PtAccount_ReqRoomList_args;

	pPtAccountModule->methods.Add(TEXT("ReqRoomList"), pPtAccount_ReqRoomList); 
	pPtAccountModule->base_methods.Add(TEXT("ReqRoomList"), pPtAccount_ReqRoomList);

	pPtAccountModule->idbase_methods.Add(pPtAccount_ReqRoomList->methodUtype, pPtAccount_ReqRoomList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(ReqRoomList / 5).");

	TArray<DATATYPE_BASE*> PtAccount_ReqSelectRoleGame_args;
	PtAccount_ReqSelectRoleGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pPtAccount_ReqSelectRoleGame = new Method();
	pPtAccount_ReqSelectRoleGame->name = TEXT("ReqSelectRoleGame");
	pPtAccount_ReqSelectRoleGame->methodUtype = 4;
	pPtAccount_ReqSelectRoleGame->aliasID = -1;
	pPtAccount_ReqSelectRoleGame->args = PtAccount_ReqSelectRoleGame_args;

	pPtAccountModule->methods.Add(TEXT("ReqSelectRoleGame"), pPtAccount_ReqSelectRoleGame); 
	pPtAccountModule->base_methods.Add(TEXT("ReqSelectRoleGame"), pPtAccount_ReqSelectRoleGame);

	pPtAccountModule->idbase_methods.Add(pPtAccount_ReqSelectRoleGame->methodUtype, pPtAccount_ReqSelectRoleGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(ReqSelectRoleGame / 4).");

	TArray<DATATYPE_BASE*> PtAccount_SelectRoomGame_args;
	PtAccount_SelectRoomGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pPtAccount_SelectRoomGame = new Method();
	pPtAccount_SelectRoomGame->name = TEXT("SelectRoomGame");
	pPtAccount_SelectRoomGame->methodUtype = 7;
	pPtAccount_SelectRoomGame->aliasID = -1;
	pPtAccount_SelectRoomGame->args = PtAccount_SelectRoomGame_args;

	pPtAccountModule->methods.Add(TEXT("SelectRoomGame"), pPtAccount_SelectRoomGame); 
	pPtAccountModule->base_methods.Add(TEXT("SelectRoomGame"), pPtAccount_SelectRoomGame);

	pPtAccountModule->idbase_methods.Add(pPtAccount_SelectRoomGame->methodUtype, pPtAccount_SelectRoomGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(SelectRoomGame / 7).");

	ScriptModule* pPtRoleModule = new ScriptModule("PtRole", 2);
	EntityDef::moduledefs.Add(TEXT("PtRole"), pPtRoleModule);
	EntityDef::idmoduledefs.Add(2, pPtRoleModule);

	Property* pPtRole_position = new Property();
	pPtRole_position->name = TEXT("position");
	pPtRole_position->properUtype = 40000;
	pPtRole_position->properFlags = 4;
	pPtRole_position->aliasID = 1;
	KBVar* pPtRole_position_defval = new KBVar(FVector());
	pPtRole_position->pDefaultVal = pPtRole_position_defval;
	pPtRoleModule->propertys.Add(TEXT("position"), pPtRole_position); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_position->aliasID, pPtRole_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(position / 40000).");

	Property* pPtRole_direction = new Property();
	pPtRole_direction->name = TEXT("direction");
	pPtRole_direction->properUtype = 40001;
	pPtRole_direction->properFlags = 4;
	pPtRole_direction->aliasID = 2;
	KBVar* pPtRole_direction_defval = new KBVar(FVector());
	pPtRole_direction->pDefaultVal = pPtRole_direction_defval;
	pPtRoleModule->propertys.Add(TEXT("direction"), pPtRole_direction); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_direction->aliasID, pPtRole_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(direction / 40001).");

	Property* pPtRole_spaceID = new Property();
	pPtRole_spaceID->name = TEXT("spaceID");
	pPtRole_spaceID->properUtype = 40002;
	pPtRole_spaceID->properFlags = 16;
	pPtRole_spaceID->aliasID = 3;
	KBVar* pPtRole_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pPtRole_spaceID->pDefaultVal = pPtRole_spaceID_defval;
	pPtRoleModule->propertys.Add(TEXT("spaceID"), pPtRole_spaceID); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_spaceID->aliasID, pPtRole_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(spaceID / 40002).");

	Property* pPtRole_BaseHP = new Property();
	pPtRole_BaseHP->name = TEXT("BaseHP");
	pPtRole_BaseHP->properUtype = 12;
	pPtRole_BaseHP->properFlags = 4;
	pPtRole_BaseHP->aliasID = 4;
	KBVar* pPtRole_BaseHP_defval = new KBVar((int16)FCString::Atoi64(TEXT("500")));
	pPtRole_BaseHP->pDefaultVal = pPtRole_BaseHP_defval;
	pPtRoleModule->propertys.Add(TEXT("BaseHP"), pPtRole_BaseHP); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_BaseHP->aliasID, pPtRole_BaseHP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(BaseHP / 12).");

	Property* pPtRole_Defense = new Property();
	pPtRole_Defense->name = TEXT("Defense");
	pPtRole_Defense->properUtype = 14;
	pPtRole_Defense->properFlags = 16;
	pPtRole_Defense->aliasID = 5;
	KBVar* pPtRole_Defense_defval = new KBVar((int16)FCString::Atoi64(TEXT("10")));
	pPtRole_Defense->pDefaultVal = pPtRole_Defense_defval;
	pPtRoleModule->propertys.Add(TEXT("Defense"), pPtRole_Defense); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_Defense->aliasID, pPtRole_Defense);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(Defense / 14).");

	Property* pPtRole_HP = new Property();
	pPtRole_HP->name = TEXT("HP");
	pPtRole_HP->properUtype = 13;
	pPtRole_HP->properFlags = 4;
	pPtRole_HP->aliasID = 6;
	KBVar* pPtRole_HP_defval = new KBVar((int16)FCString::Atoi64(TEXT("500")));
	pPtRole_HP->pDefaultVal = pPtRole_HP_defval;
	pPtRoleModule->propertys.Add(TEXT("HP"), pPtRole_HP); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_HP->aliasID, pPtRole_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(HP / 13).");

	Property* pPtRole_Name = new Property();
	pPtRole_Name->name = TEXT("Name");
	pPtRole_Name->properUtype = 10;
	pPtRole_Name->properFlags = 4;
	pPtRole_Name->aliasID = 7;
	KBVar* pPtRole_Name_defval = new KBVar(FString());
	pPtRole_Name->pDefaultVal = pPtRole_Name_defval;
	pPtRoleModule->propertys.Add(TEXT("Name"), pPtRole_Name); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_Name->aliasID, pPtRole_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(Name / 10).");

	Property* pPtRole_PowerRatio = new Property();
	pPtRole_PowerRatio->name = TEXT("PowerRatio");
	pPtRole_PowerRatio->properUtype = 15;
	pPtRole_PowerRatio->properFlags = 16;
	pPtRole_PowerRatio->aliasID = 8;
	KBVar* pPtRole_PowerRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pPtRole_PowerRatio->pDefaultVal = pPtRole_PowerRatio_defval;
	pPtRoleModule->propertys.Add(TEXT("PowerRatio"), pPtRole_PowerRatio); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_PowerRatio->aliasID, pPtRole_PowerRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(PowerRatio / 15).");

	Property* pPtRole_RoleType = new Property();
	pPtRole_RoleType->name = TEXT("RoleType");
	pPtRole_RoleType->properUtype = 11;
	pPtRole_RoleType->properFlags = 4;
	pPtRole_RoleType->aliasID = 9;
	KBVar* pPtRole_RoleType_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pPtRole_RoleType->pDefaultVal = pPtRole_RoleType_defval;
	pPtRoleModule->propertys.Add(TEXT("RoleType"), pPtRole_RoleType); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_RoleType->aliasID, pPtRole_RoleType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(RoleType / 11).");

	Property* pPtRole_SpawnPoint = new Property();
	pPtRole_SpawnPoint->name = TEXT("SpawnPoint");
	pPtRole_SpawnPoint->properUtype = 4;
	pPtRole_SpawnPoint->properFlags = 16;
	pPtRole_SpawnPoint->aliasID = 10;
	KBVar* pPtRole_SpawnPoint_defval = new KBVar(FVector());
	pPtRole_SpawnPoint->pDefaultVal = pPtRole_SpawnPoint_defval;
	pPtRoleModule->propertys.Add(TEXT("SpawnPoint"), pPtRole_SpawnPoint); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_SpawnPoint->aliasID, pPtRole_SpawnPoint);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(SpawnPoint / 4).");

	Property* pPtRole_SpeedRatio = new Property();
	pPtRole_SpeedRatio->name = TEXT("SpeedRatio");
	pPtRole_SpeedRatio->properUtype = 16;
	pPtRole_SpeedRatio->properFlags = 16;
	pPtRole_SpeedRatio->aliasID = 11;
	KBVar* pPtRole_SpeedRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pPtRole_SpeedRatio->pDefaultVal = pPtRole_SpeedRatio_defval;
	pPtRoleModule->propertys.Add(TEXT("SpeedRatio"), pPtRole_SpeedRatio); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_SpeedRatio->aliasID, pPtRole_SpeedRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(SpeedRatio / 16).");

	TArray<DATATYPE_BASE*> PtRole_OnAcceptChatList_args;
	PtRole_OnAcceptChatList_args.Add(EntityDef::id2datatypes[36]);

	Method* pPtRole_OnAcceptChatList = new Method();
	pPtRole_OnAcceptChatList->name = TEXT("OnAcceptChatList");
	pPtRole_OnAcceptChatList->methodUtype = 23;
	pPtRole_OnAcceptChatList->aliasID = 1;
	pPtRole_OnAcceptChatList->args = PtRole_OnAcceptChatList_args;

	pPtRoleModule->methods.Add(TEXT("OnAcceptChatList"), pPtRole_OnAcceptChatList); 
	pPtRoleModule->useMethodDescrAlias = true;
	pPtRoleModule->idmethods.Add((uint16)pPtRole_OnAcceptChatList->aliasID, pPtRole_OnAcceptChatList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(OnAcceptChatList / 23).");

	TArray<DATATYPE_BASE*> PtRole_OnAnimUpdate_args;
	PtRole_OnAnimUpdate_args.Add(EntityDef::id2datatypes[30]);

	Method* pPtRole_OnAnimUpdate = new Method();
	pPtRole_OnAnimUpdate->name = TEXT("OnAnimUpdate");
	pPtRole_OnAnimUpdate->methodUtype = 32;
	pPtRole_OnAnimUpdate->aliasID = 2;
	pPtRole_OnAnimUpdate->args = PtRole_OnAnimUpdate_args;

	pPtRoleModule->methods.Add(TEXT("OnAnimUpdate"), pPtRole_OnAnimUpdate); 
	pPtRoleModule->useMethodDescrAlias = true;
	pPtRoleModule->idmethods.Add((uint16)pPtRole_OnAnimUpdate->aliasID, pPtRole_OnAnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(OnAnimUpdate / 32).");

	TArray<DATATYPE_BASE*> PtRole_OnAttack_args;
	PtRole_OnAttack_args.Add(EntityDef::id2datatypes[2]);

	Method* pPtRole_OnAttack = new Method();
	pPtRole_OnAttack->name = TEXT("OnAttack");
	pPtRole_OnAttack->methodUtype = 30;
	pPtRole_OnAttack->aliasID = 3;
	pPtRole_OnAttack->args = PtRole_OnAttack_args;

	pPtRoleModule->methods.Add(TEXT("OnAttack"), pPtRole_OnAttack); 
	pPtRoleModule->useMethodDescrAlias = true;
	pPtRoleModule->idmethods.Add((uint16)pPtRole_OnAttack->aliasID, pPtRole_OnAttack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(OnAttack / 30).");

	TArray<DATATYPE_BASE*> PtRole_OnIncreaseGood_args;
	PtRole_OnIncreaseGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_OnIncreaseGood_args.Add(EntityDef::id2datatypes[31]);

	Method* pPtRole_OnIncreaseGood = new Method();
	pPtRole_OnIncreaseGood->name = TEXT("OnIncreaseGood");
	pPtRole_OnIncreaseGood->methodUtype = 20;
	pPtRole_OnIncreaseGood->aliasID = 4;
	pPtRole_OnIncreaseGood->args = PtRole_OnIncreaseGood_args;

	pPtRoleModule->methods.Add(TEXT("OnIncreaseGood"), pPtRole_OnIncreaseGood); 
	pPtRoleModule->useMethodDescrAlias = true;
	pPtRoleModule->idmethods.Add((uint16)pPtRole_OnIncreaseGood->aliasID, pPtRole_OnIncreaseGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(OnIncreaseGood / 20).");

	TArray<DATATYPE_BASE*> PtRole_OnPassGood_args;
	PtRole_OnPassGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_OnPassGood_args.Add(EntityDef::id2datatypes[31]);
	PtRole_OnPassGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_OnPassGood_args.Add(EntityDef::id2datatypes[31]);

	Method* pPtRole_OnPassGood = new Method();
	pPtRole_OnPassGood->name = TEXT("OnPassGood");
	pPtRole_OnPassGood->methodUtype = 22;
	pPtRole_OnPassGood->aliasID = 5;
	pPtRole_OnPassGood->args = PtRole_OnPassGood_args;

	pPtRoleModule->methods.Add(TEXT("OnPassGood"), pPtRole_OnPassGood); 
	pPtRoleModule->useMethodDescrAlias = true;
	pPtRoleModule->idmethods.Add((uint16)pPtRole_OnPassGood->aliasID, pPtRole_OnPassGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(OnPassGood / 22).");

	TArray<DATATYPE_BASE*> PtRole_OnReduceGood_args;
	PtRole_OnReduceGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_OnReduceGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_OnReduceGood_args.Add(EntityDef::id2datatypes[31]);

	Method* pPtRole_OnReduceGood = new Method();
	pPtRole_OnReduceGood->name = TEXT("OnReduceGood");
	pPtRole_OnReduceGood->methodUtype = 21;
	pPtRole_OnReduceGood->aliasID = 6;
	pPtRole_OnReduceGood->args = PtRole_OnReduceGood_args;

	pPtRoleModule->methods.Add(TEXT("OnReduceGood"), pPtRole_OnReduceGood); 
	pPtRoleModule->useMethodDescrAlias = true;
	pPtRoleModule->idmethods.Add((uint16)pPtRole_OnReduceGood->aliasID, pPtRole_OnReduceGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(OnReduceGood / 21).");

	TArray<DATATYPE_BASE*> PtRole_OnReqBagList_args;
	PtRole_OnReqBagList_args.Add(EntityDef::id2datatypes[32]);
	PtRole_OnReqBagList_args.Add(EntityDef::id2datatypes[32]);
	PtRole_OnReqBagList_args.Add(EntityDef::id2datatypes[32]);
	PtRole_OnReqBagList_args.Add(EntityDef::id2datatypes[32]);

	Method* pPtRole_OnReqBagList = new Method();
	pPtRole_OnReqBagList->name = TEXT("OnReqBagList");
	pPtRole_OnReqBagList->methodUtype = 19;
	pPtRole_OnReqBagList->aliasID = 7;
	pPtRole_OnReqBagList->args = PtRole_OnReqBagList_args;

	pPtRoleModule->methods.Add(TEXT("OnReqBagList"), pPtRole_OnReqBagList); 
	pPtRoleModule->useMethodDescrAlias = true;
	pPtRoleModule->idmethods.Add((uint16)pPtRole_OnReqBagList->aliasID, pPtRole_OnReqBagList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(OnReqBagList / 19).");

	TArray<DATATYPE_BASE*> PtRole_PassGood_args;
	PtRole_PassGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_PassGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_PassGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_PassGood_args.Add(EntityDef::id2datatypes[2]);

	Method* pPtRole_PassGood = new Method();
	pPtRole_PassGood->name = TEXT("PassGood");
	pPtRole_PassGood->methodUtype = 17;
	pPtRole_PassGood->aliasID = -1;
	pPtRole_PassGood->args = PtRole_PassGood_args;

	pPtRoleModule->methods.Add(TEXT("PassGood"), pPtRole_PassGood); 
	pPtRoleModule->base_methods.Add(TEXT("PassGood"), pPtRole_PassGood);

	pPtRoleModule->idbase_methods.Add(pPtRole_PassGood->methodUtype, pPtRole_PassGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(PassGood / 17).");

	TArray<DATATYPE_BASE*> PtRole_ReduceGood_args;
	PtRole_ReduceGood_args.Add(EntityDef::id2datatypes[2]);
	PtRole_ReduceGood_args.Add(EntityDef::id2datatypes[2]);

	Method* pPtRole_ReduceGood = new Method();
	pPtRole_ReduceGood->name = TEXT("ReduceGood");
	pPtRole_ReduceGood->methodUtype = 16;
	pPtRole_ReduceGood->aliasID = -1;
	pPtRole_ReduceGood->args = PtRole_ReduceGood_args;

	pPtRoleModule->methods.Add(TEXT("ReduceGood"), pPtRole_ReduceGood); 
	pPtRoleModule->base_methods.Add(TEXT("ReduceGood"), pPtRole_ReduceGood);

	pPtRoleModule->idbase_methods.Add(pPtRole_ReduceGood->methodUtype, pPtRole_ReduceGood);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(ReduceGood / 16).");

	TArray<DATATYPE_BASE*> PtRole_ReqBagList_args;

	Method* pPtRole_ReqBagList = new Method();
	pPtRole_ReqBagList->name = TEXT("ReqBagList");
	pPtRole_ReqBagList->methodUtype = 14;
	pPtRole_ReqBagList->aliasID = -1;
	pPtRole_ReqBagList->args = PtRole_ReqBagList_args;

	pPtRoleModule->methods.Add(TEXT("ReqBagList"), pPtRole_ReqBagList); 
	pPtRoleModule->base_methods.Add(TEXT("ReqBagList"), pPtRole_ReqBagList);

	pPtRoleModule->idbase_methods.Add(pPtRole_ReqBagList->methodUtype, pPtRole_ReqBagList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(ReqBagList / 14).");

	TArray<DATATYPE_BASE*> PtRole_SendChatInfo_args;
	PtRole_SendChatInfo_args.Add(EntityDef::id2datatypes[12]);

	Method* pPtRole_SendChatInfo = new Method();
	pPtRole_SendChatInfo->name = TEXT("SendChatInfo");
	pPtRole_SendChatInfo->methodUtype = 18;
	pPtRole_SendChatInfo->aliasID = -1;
	pPtRole_SendChatInfo->args = PtRole_SendChatInfo_args;

	pPtRoleModule->methods.Add(TEXT("SendChatInfo"), pPtRole_SendChatInfo); 
	pPtRoleModule->base_methods.Add(TEXT("SendChatInfo"), pPtRole_SendChatInfo);

	pPtRoleModule->idbase_methods.Add(pPtRole_SendChatInfo->methodUtype, pPtRole_SendChatInfo);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(SendChatInfo / 18).");

	TArray<DATATYPE_BASE*> PtRole_AnimUpdate_args;
	PtRole_AnimUpdate_args.Add(EntityDef::id2datatypes[30]);

	Method* pPtRole_AnimUpdate = new Method();
	pPtRole_AnimUpdate->name = TEXT("AnimUpdate");
	pPtRole_AnimUpdate->methodUtype = 31;
	pPtRole_AnimUpdate->aliasID = -1;
	pPtRole_AnimUpdate->args = PtRole_AnimUpdate_args;

	pPtRoleModule->methods.Add(TEXT("AnimUpdate"), pPtRole_AnimUpdate); 
	pPtRoleModule->cell_methods.Add(TEXT("AnimUpdate"), pPtRole_AnimUpdate);

	pPtRoleModule->idcell_methods.Add(pPtRole_AnimUpdate->methodUtype, pPtRole_AnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(AnimUpdate / 31).");

	TArray<DATATYPE_BASE*> PtRole_Attack_args;
	PtRole_Attack_args.Add(EntityDef::id2datatypes[34]);

	Method* pPtRole_Attack = new Method();
	pPtRole_Attack->name = TEXT("Attack");
	pPtRole_Attack->methodUtype = 25;
	pPtRole_Attack->aliasID = -1;
	pPtRole_Attack->args = PtRole_Attack_args;

	pPtRoleModule->methods.Add(TEXT("Attack"), pPtRole_Attack); 
	pPtRoleModule->cell_methods.Add(TEXT("Attack"), pPtRole_Attack);

	pPtRoleModule->idcell_methods.Add(pPtRole_Attack->methodUtype, pPtRole_Attack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(Attack / 25).");

	TArray<DATATYPE_BASE*> PtRole_Relive_args;

	Method* pPtRole_Relive = new Method();
	pPtRole_Relive->name = TEXT("Relive");
	pPtRole_Relive->methodUtype = 24;
	pPtRole_Relive->aliasID = -1;
	pPtRole_Relive->args = PtRole_Relive_args;

	pPtRoleModule->methods.Add(TEXT("Relive"), pPtRole_Relive); 
	pPtRoleModule->cell_methods.Add(TEXT("Relive"), pPtRole_Relive);

	pPtRoleModule->idcell_methods.Add(pPtRole_Relive->methodUtype, pPtRole_Relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(Relive / 24).");

	ScriptModule* pPtMonsterModule = new ScriptModule("PtMonster", 5);
	EntityDef::moduledefs.Add(TEXT("PtMonster"), pPtMonsterModule);
	EntityDef::idmoduledefs.Add(5, pPtMonsterModule);

	Property* pPtMonster_position = new Property();
	pPtMonster_position->name = TEXT("position");
	pPtMonster_position->properUtype = 40000;
	pPtMonster_position->properFlags = 4;
	pPtMonster_position->aliasID = 1;
	KBVar* pPtMonster_position_defval = new KBVar(FVector());
	pPtMonster_position->pDefaultVal = pPtMonster_position_defval;
	pPtMonsterModule->propertys.Add(TEXT("position"), pPtMonster_position); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_position->aliasID, pPtMonster_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(position / 40000).");

	Property* pPtMonster_direction = new Property();
	pPtMonster_direction->name = TEXT("direction");
	pPtMonster_direction->properUtype = 40001;
	pPtMonster_direction->properFlags = 4;
	pPtMonster_direction->aliasID = 2;
	KBVar* pPtMonster_direction_defval = new KBVar(FVector());
	pPtMonster_direction->pDefaultVal = pPtMonster_direction_defval;
	pPtMonsterModule->propertys.Add(TEXT("direction"), pPtMonster_direction); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_direction->aliasID, pPtMonster_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(direction / 40001).");

	Property* pPtMonster_spaceID = new Property();
	pPtMonster_spaceID->name = TEXT("spaceID");
	pPtMonster_spaceID->properUtype = 40002;
	pPtMonster_spaceID->properFlags = 16;
	pPtMonster_spaceID->aliasID = 3;
	KBVar* pPtMonster_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pPtMonster_spaceID->pDefaultVal = pPtMonster_spaceID_defval;
	pPtMonsterModule->propertys.Add(TEXT("spaceID"), pPtMonster_spaceID); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_spaceID->aliasID, pPtMonster_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(spaceID / 40002).");

	Property* pPtMonster_BaseHP = new Property();
	pPtMonster_BaseHP->name = TEXT("BaseHP");
	pPtMonster_BaseHP->properUtype = 24;
	pPtMonster_BaseHP->properFlags = 4;
	pPtMonster_BaseHP->aliasID = 4;
	KBVar* pPtMonster_BaseHP_defval = new KBVar((int16)FCString::Atoi64(TEXT("500")));
	pPtMonster_BaseHP->pDefaultVal = pPtMonster_BaseHP_defval;
	pPtMonsterModule->propertys.Add(TEXT("BaseHP"), pPtMonster_BaseHP); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_BaseHP->aliasID, pPtMonster_BaseHP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(BaseHP / 24).");

	Property* pPtMonster_Defense = new Property();
	pPtMonster_Defense->name = TEXT("Defense");
	pPtMonster_Defense->properUtype = 26;
	pPtMonster_Defense->properFlags = 16;
	pPtMonster_Defense->aliasID = 5;
	KBVar* pPtMonster_Defense_defval = new KBVar((int16)FCString::Atoi64(TEXT("10")));
	pPtMonster_Defense->pDefaultVal = pPtMonster_Defense_defval;
	pPtMonsterModule->propertys.Add(TEXT("Defense"), pPtMonster_Defense); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_Defense->aliasID, pPtMonster_Defense);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(Defense / 26).");

	Property* pPtMonster_HP = new Property();
	pPtMonster_HP->name = TEXT("HP");
	pPtMonster_HP->properUtype = 25;
	pPtMonster_HP->properFlags = 4;
	pPtMonster_HP->aliasID = 6;
	KBVar* pPtMonster_HP_defval = new KBVar((int16)FCString::Atoi64(TEXT("500")));
	pPtMonster_HP->pDefaultVal = pPtMonster_HP_defval;
	pPtMonsterModule->propertys.Add(TEXT("HP"), pPtMonster_HP); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_HP->aliasID, pPtMonster_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(HP / 25).");

	Property* pPtMonster_Name = new Property();
	pPtMonster_Name->name = TEXT("Name");
	pPtMonster_Name->properUtype = 22;
	pPtMonster_Name->properFlags = 4;
	pPtMonster_Name->aliasID = 7;
	KBVar* pPtMonster_Name_defval = new KBVar(FString());
	pPtMonster_Name->pDefaultVal = pPtMonster_Name_defval;
	pPtMonsterModule->propertys.Add(TEXT("Name"), pPtMonster_Name); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_Name->aliasID, pPtMonster_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(Name / 22).");

	Property* pPtMonster_PowerRatio = new Property();
	pPtMonster_PowerRatio->name = TEXT("PowerRatio");
	pPtMonster_PowerRatio->properUtype = 27;
	pPtMonster_PowerRatio->properFlags = 16;
	pPtMonster_PowerRatio->aliasID = 8;
	KBVar* pPtMonster_PowerRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pPtMonster_PowerRatio->pDefaultVal = pPtMonster_PowerRatio_defval;
	pPtMonsterModule->propertys.Add(TEXT("PowerRatio"), pPtMonster_PowerRatio); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_PowerRatio->aliasID, pPtMonster_PowerRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(PowerRatio / 27).");

	Property* pPtMonster_RoleType = new Property();
	pPtMonster_RoleType->name = TEXT("RoleType");
	pPtMonster_RoleType->properUtype = 23;
	pPtMonster_RoleType->properFlags = 4;
	pPtMonster_RoleType->aliasID = 9;
	KBVar* pPtMonster_RoleType_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pPtMonster_RoleType->pDefaultVal = pPtMonster_RoleType_defval;
	pPtMonsterModule->propertys.Add(TEXT("RoleType"), pPtMonster_RoleType); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_RoleType->aliasID, pPtMonster_RoleType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(RoleType / 23).");

	Property* pPtMonster_SpeedRatio = new Property();
	pPtMonster_SpeedRatio->name = TEXT("SpeedRatio");
	pPtMonster_SpeedRatio->properUtype = 28;
	pPtMonster_SpeedRatio->properFlags = 16;
	pPtMonster_SpeedRatio->aliasID = 10;
	KBVar* pPtMonster_SpeedRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pPtMonster_SpeedRatio->pDefaultVal = pPtMonster_SpeedRatio_defval;
	pPtMonsterModule->propertys.Add(TEXT("SpeedRatio"), pPtMonster_SpeedRatio); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_SpeedRatio->aliasID, pPtMonster_SpeedRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(SpeedRatio / 28).");

	TArray<DATATYPE_BASE*> PtMonster_OnAnimUpdate_args;
	PtMonster_OnAnimUpdate_args.Add(EntityDef::id2datatypes[30]);

	Method* pPtMonster_OnAnimUpdate = new Method();
	pPtMonster_OnAnimUpdate->name = TEXT("OnAnimUpdate");
	pPtMonster_OnAnimUpdate->methodUtype = 41;
	pPtMonster_OnAnimUpdate->aliasID = 1;
	pPtMonster_OnAnimUpdate->args = PtMonster_OnAnimUpdate_args;

	pPtMonsterModule->methods.Add(TEXT("OnAnimUpdate"), pPtMonster_OnAnimUpdate); 
	pPtMonsterModule->useMethodDescrAlias = true;
	pPtMonsterModule->idmethods.Add((uint16)pPtMonster_OnAnimUpdate->aliasID, pPtMonster_OnAnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), method(OnAnimUpdate / 41).");

	TArray<DATATYPE_BASE*> PtMonster_OnAttack_args;
	PtMonster_OnAttack_args.Add(EntityDef::id2datatypes[2]);

	Method* pPtMonster_OnAttack = new Method();
	pPtMonster_OnAttack->name = TEXT("OnAttack");
	pPtMonster_OnAttack->methodUtype = 39;
	pPtMonster_OnAttack->aliasID = 2;
	pPtMonster_OnAttack->args = PtMonster_OnAttack_args;

	pPtMonsterModule->methods.Add(TEXT("OnAttack"), pPtMonster_OnAttack); 
	pPtMonsterModule->useMethodDescrAlias = true;
	pPtMonsterModule->idmethods.Add((uint16)pPtMonster_OnAttack->aliasID, pPtMonster_OnAttack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), method(OnAttack / 39).");

	TArray<DATATYPE_BASE*> PtMonster_AnimUpdate_args;
	PtMonster_AnimUpdate_args.Add(EntityDef::id2datatypes[30]);

	Method* pPtMonster_AnimUpdate = new Method();
	pPtMonster_AnimUpdate->name = TEXT("AnimUpdate");
	pPtMonster_AnimUpdate->methodUtype = 40;
	pPtMonster_AnimUpdate->aliasID = -1;
	pPtMonster_AnimUpdate->args = PtMonster_AnimUpdate_args;

	pPtMonsterModule->methods.Add(TEXT("AnimUpdate"), pPtMonster_AnimUpdate); 
	pPtMonsterModule->cell_methods.Add(TEXT("AnimUpdate"), pPtMonster_AnimUpdate);

	pPtMonsterModule->idcell_methods.Add(pPtMonster_AnimUpdate->methodUtype, pPtMonster_AnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), method(AnimUpdate / 40).");

	TArray<DATATYPE_BASE*> PtMonster_Attack_args;
	PtMonster_Attack_args.Add(EntityDef::id2datatypes[34]);

	Method* pPtMonster_Attack = new Method();
	pPtMonster_Attack->name = TEXT("Attack");
	pPtMonster_Attack->methodUtype = 34;
	pPtMonster_Attack->aliasID = -1;
	pPtMonster_Attack->args = PtMonster_Attack_args;

	pPtMonsterModule->methods.Add(TEXT("Attack"), pPtMonster_Attack); 
	pPtMonsterModule->cell_methods.Add(TEXT("Attack"), pPtMonster_Attack);

	pPtMonsterModule->idcell_methods.Add(pPtMonster_Attack->methodUtype, pPtMonster_Attack);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), method(Attack / 34).");

	TArray<DATATYPE_BASE*> PtMonster_Relive_args;

	Method* pPtMonster_Relive = new Method();
	pPtMonster_Relive->name = TEXT("Relive");
	pPtMonster_Relive->methodUtype = 33;
	pPtMonster_Relive->aliasID = -1;
	pPtMonster_Relive->args = PtMonster_Relive_args;

	pPtMonsterModule->methods.Add(TEXT("Relive"), pPtMonster_Relive); 
	pPtMonsterModule->cell_methods.Add(TEXT("Relive"), pPtMonster_Relive);

	pPtMonsterModule->idcell_methods.Add(pPtMonster_Relive->methodUtype, pPtMonster_Relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), method(Relive / 33).");

	ScriptModule* pPtFlobModule = new ScriptModule("PtFlob", 6);
	EntityDef::moduledefs.Add(TEXT("PtFlob"), pPtFlobModule);
	EntityDef::idmoduledefs.Add(6, pPtFlobModule);

	Property* pPtFlob_position = new Property();
	pPtFlob_position->name = TEXT("position");
	pPtFlob_position->properUtype = 40000;
	pPtFlob_position->properFlags = 4;
	pPtFlob_position->aliasID = 1;
	KBVar* pPtFlob_position_defval = new KBVar(FVector());
	pPtFlob_position->pDefaultVal = pPtFlob_position_defval;
	pPtFlobModule->propertys.Add(TEXT("position"), pPtFlob_position); 

	pPtFlobModule->usePropertyDescrAlias = true;
	pPtFlobModule->idpropertys.Add((uint16)pPtFlob_position->aliasID, pPtFlob_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtFlob), property(position / 40000).");

	Property* pPtFlob_direction = new Property();
	pPtFlob_direction->name = TEXT("direction");
	pPtFlob_direction->properUtype = 40001;
	pPtFlob_direction->properFlags = 4;
	pPtFlob_direction->aliasID = 2;
	KBVar* pPtFlob_direction_defval = new KBVar(FVector());
	pPtFlob_direction->pDefaultVal = pPtFlob_direction_defval;
	pPtFlobModule->propertys.Add(TEXT("direction"), pPtFlob_direction); 

	pPtFlobModule->usePropertyDescrAlias = true;
	pPtFlobModule->idpropertys.Add((uint16)pPtFlob_direction->aliasID, pPtFlob_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtFlob), property(direction / 40001).");

	Property* pPtFlob_spaceID = new Property();
	pPtFlob_spaceID->name = TEXT("spaceID");
	pPtFlob_spaceID->properUtype = 40002;
	pPtFlob_spaceID->properFlags = 16;
	pPtFlob_spaceID->aliasID = 3;
	KBVar* pPtFlob_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pPtFlob_spaceID->pDefaultVal = pPtFlob_spaceID_defval;
	pPtFlobModule->propertys.Add(TEXT("spaceID"), pPtFlob_spaceID); 

	pPtFlobModule->usePropertyDescrAlias = true;
	pPtFlobModule->idpropertys.Add((uint16)pPtFlob_spaceID->aliasID, pPtFlob_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtFlob), property(spaceID / 40002).");

	Property* pPtFlob_GoodId = new Property();
	pPtFlob_GoodId->name = TEXT("GoodId");
	pPtFlob_GoodId->properUtype = 37;
	pPtFlob_GoodId->properFlags = 4;
	pPtFlob_GoodId->aliasID = 4;
	KBVar* pPtFlob_GoodId_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pPtFlob_GoodId->pDefaultVal = pPtFlob_GoodId_defval;
	pPtFlobModule->propertys.Add(TEXT("GoodId"), pPtFlob_GoodId); 

	pPtFlobModule->usePropertyDescrAlias = true;
	pPtFlobModule->idpropertys.Add((uint16)pPtFlob_GoodId->aliasID, pPtFlob_GoodId);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtFlob), property(GoodId / 37).");

	pPtFlobModule->useMethodDescrAlias = true;
	ScriptModule* pPtSkillModule = new ScriptModule("PtSkill", 7);
	EntityDef::moduledefs.Add(TEXT("PtSkill"), pPtSkillModule);
	EntityDef::idmoduledefs.Add(7, pPtSkillModule);

	Property* pPtSkill_position = new Property();
	pPtSkill_position->name = TEXT("position");
	pPtSkill_position->properUtype = 40000;
	pPtSkill_position->properFlags = 4;
	pPtSkill_position->aliasID = 1;
	KBVar* pPtSkill_position_defval = new KBVar(FVector());
	pPtSkill_position->pDefaultVal = pPtSkill_position_defval;
	pPtSkillModule->propertys.Add(TEXT("position"), pPtSkill_position); 

	pPtSkillModule->usePropertyDescrAlias = true;
	pPtSkillModule->idpropertys.Add((uint16)pPtSkill_position->aliasID, pPtSkill_position);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtSkill), property(position / 40000).");

	Property* pPtSkill_direction = new Property();
	pPtSkill_direction->name = TEXT("direction");
	pPtSkill_direction->properUtype = 40001;
	pPtSkill_direction->properFlags = 4;
	pPtSkill_direction->aliasID = 2;
	KBVar* pPtSkill_direction_defval = new KBVar(FVector());
	pPtSkill_direction->pDefaultVal = pPtSkill_direction_defval;
	pPtSkillModule->propertys.Add(TEXT("direction"), pPtSkill_direction); 

	pPtSkillModule->usePropertyDescrAlias = true;
	pPtSkillModule->idpropertys.Add((uint16)pPtSkill_direction->aliasID, pPtSkill_direction);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtSkill), property(direction / 40001).");

	Property* pPtSkill_spaceID = new Property();
	pPtSkill_spaceID->name = TEXT("spaceID");
	pPtSkill_spaceID->properUtype = 40002;
	pPtSkill_spaceID->properFlags = 16;
	pPtSkill_spaceID->aliasID = 3;
	KBVar* pPtSkill_spaceID_defval = new KBVar((uint32)FCString::Atoi64(TEXT("")));
	pPtSkill_spaceID->pDefaultVal = pPtSkill_spaceID_defval;
	pPtSkillModule->propertys.Add(TEXT("spaceID"), pPtSkill_spaceID); 

	pPtSkillModule->usePropertyDescrAlias = true;
	pPtSkillModule->idpropertys.Add((uint16)pPtSkill_spaceID->aliasID, pPtSkill_spaceID);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtSkill), property(spaceID / 40002).");

	Property* pPtSkill_SkillId = new Property();
	pPtSkill_SkillId->name = TEXT("SkillId");
	pPtSkill_SkillId->properUtype = 41;
	pPtSkill_SkillId->properFlags = 4;
	pPtSkill_SkillId->aliasID = 4;
	KBVar* pPtSkill_SkillId_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pPtSkill_SkillId->pDefaultVal = pPtSkill_SkillId_defval;
	pPtSkillModule->propertys.Add(TEXT("SkillId"), pPtSkill_SkillId); 

	pPtSkillModule->usePropertyDescrAlias = true;
	pPtSkillModule->idpropertys.Add((uint16)pPtSkill_SkillId->aliasID, pPtSkill_SkillId);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtSkill), property(SkillId / 41).");

	pPtSkillModule->useMethodDescrAlias = true;
}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("REDUCE_RES");
		FString name = TEXT("UINT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 3;
		FString typeName = TEXT("UINT16");
		FString name = TEXT("UINT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 5;
		FString typeName = TEXT("DBID");
		FString name = TEXT("UINT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 4;
		FString typeName = TEXT("UINT32");
		FString name = TEXT("UINT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 6;
		FString typeName = TEXT("INT8");
		FString name = TEXT("INT8");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 7;
		FString typeName = TEXT("INT16");
		FString name = TEXT("INT16");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 8;
		FString typeName = TEXT("ENTITY_ID");
		FString name = TEXT("INT32");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 9;
		FString typeName = TEXT("INT64");
		FString name = TEXT("INT64");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 1;
		FString typeName = TEXT("STRING");
		FString name = TEXT("STRING");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 12;
		FString typeName = TEXT("UNICODE");
		FString name = TEXT("UNICODE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 13;
		FString typeName = TEXT("FLOAT");
		FString name = TEXT("FLOAT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 14;
		FString typeName = TEXT("DOUBLE");
		FString name = TEXT("DOUBLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PYTHON");
		FString name = TEXT("PYTHON");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_DICT");
		FString name = TEXT("PY_DICT");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_TUPLE");
		FString name = TEXT("PY_TUPLE");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 10;
		FString typeName = TEXT("PY_LIST");
		FString name = TEXT("PY_LIST");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 20;
		FString typeName = TEXT("ENTITYCALL");
		FString name = TEXT("ENTITYCALL");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 11;
		FString typeName = TEXT("BLOB");
		FString name = TEXT("BLOB");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 15;
		FString typeName = TEXT("VECTOR2");
		FString name = TEXT("VECTOR2");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 16;
		FString typeName = TEXT("VECTOR3");
		FString name = TEXT("VECTOR3");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 17;
		FString typeName = TEXT("VECTOR4");
		FString name = TEXT("VECTOR4");
		DATATYPE_BASE** fPtr = EntityDef::datatypes.Find(name);
		DATATYPE_BASE* pVal = fPtr != NULL ? *fPtr : NULL;
		EntityDef::datatypes.Add(typeName, pVal);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 22;
		FString typeName = TEXT("ENTITYID_LIST");
		DATATYPE_ENTITYID_LIST* pDatatype = new DATATYPE_ENTITYID_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 23;
		FString typeName = TEXT("ROLE_DATA");
		DATATYPE_ROLE_DATA* pDatatype = new DATATYPE_ROLE_DATA();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 24;
		FString typeName = TEXT("ROLE_INFO");
		DATATYPE_ROLE_INFO* pDatatype = new DATATYPE_ROLE_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 25;
		FString typeName = TEXT("ROLE_LIST");
		DATATYPE_ROLE_LIST* pDatatype = new DATATYPE_ROLE_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 27;
		FString typeName = TEXT("ROOM_INFO");
		DATATYPE_ROOM_INFO* pDatatype = new DATATYPE_ROOM_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 28;
		FString typeName = TEXT("ROOM_LIST");
		DATATYPE_ROOM_LIST* pDatatype = new DATATYPE_ROOM_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 30;
		FString typeName = TEXT("ANIM_INFO");
		DATATYPE_ANIM_INFO* pDatatype = new DATATYPE_ANIM_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 31;
		FString typeName = TEXT("GOOD_INFO");
		DATATYPE_GOOD_INFO* pDatatype = new DATATYPE_GOOD_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 32;
		FString typeName = TEXT("BAG_INFO");
		DATATYPE_BAG_INFO* pDatatype = new DATATYPE_BAG_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 34;
		FString typeName = TEXT("SKILL_INFO");
		DATATYPE_SKILL_INFO* pDatatype = new DATATYPE_SKILL_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 35;
		FString typeName = TEXT("CHAT_INFO");
		DATATYPE_CHAT_INFO* pDatatype = new DATATYPE_CHAT_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 36;
		FString typeName = TEXT("CHAT_LIST");
		DATATYPE_CHAT_LIST* pDatatype = new DATATYPE_CHAT_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	for(auto& Elem : EntityDef::datatypes)
	{
		if(Elem.Value)
		{
			Elem.Value->bind();
		}
	}
}


}