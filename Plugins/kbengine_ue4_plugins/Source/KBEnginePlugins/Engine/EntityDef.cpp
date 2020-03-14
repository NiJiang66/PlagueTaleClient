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
	PtAccount_OnCreateRoleResult_args.Add(EntityDef::id2datatypes[23]);

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
	PtAccount_OnCreateRoom_args.Add(EntityDef::id2datatypes[26]);

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
	PtAccount_OnReqRoleList_args.Add(EntityDef::id2datatypes[24]);

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
	PtAccount_OnReqRoomList_args.Add(EntityDef::id2datatypes[27]);

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
	pPtRole_BaseHP->properUtype = 7;
	pPtRole_BaseHP->properFlags = 4;
	pPtRole_BaseHP->aliasID = 4;
	KBVar* pPtRole_BaseHP_defval = new KBVar((int16)FCString::Atoi64(TEXT("500")));
	pPtRole_BaseHP->pDefaultVal = pPtRole_BaseHP_defval;
	pPtRoleModule->propertys.Add(TEXT("BaseHP"), pPtRole_BaseHP); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_BaseHP->aliasID, pPtRole_BaseHP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(BaseHP / 7).");

	Property* pPtRole_Defense = new Property();
	pPtRole_Defense->name = TEXT("Defense");
	pPtRole_Defense->properUtype = 9;
	pPtRole_Defense->properFlags = 16;
	pPtRole_Defense->aliasID = 5;
	KBVar* pPtRole_Defense_defval = new KBVar((int16)FCString::Atoi64(TEXT("10")));
	pPtRole_Defense->pDefaultVal = pPtRole_Defense_defval;
	pPtRoleModule->propertys.Add(TEXT("Defense"), pPtRole_Defense); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_Defense->aliasID, pPtRole_Defense);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(Defense / 9).");

	Property* pPtRole_HP = new Property();
	pPtRole_HP->name = TEXT("HP");
	pPtRole_HP->properUtype = 8;
	pPtRole_HP->properFlags = 4;
	pPtRole_HP->aliasID = 6;
	KBVar* pPtRole_HP_defval = new KBVar((int16)FCString::Atoi64(TEXT("500")));
	pPtRole_HP->pDefaultVal = pPtRole_HP_defval;
	pPtRoleModule->propertys.Add(TEXT("HP"), pPtRole_HP); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_HP->aliasID, pPtRole_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(HP / 8).");

	Property* pPtRole_Name = new Property();
	pPtRole_Name->name = TEXT("Name");
	pPtRole_Name->properUtype = 5;
	pPtRole_Name->properFlags = 4;
	pPtRole_Name->aliasID = 7;
	KBVar* pPtRole_Name_defval = new KBVar(FString());
	pPtRole_Name->pDefaultVal = pPtRole_Name_defval;
	pPtRoleModule->propertys.Add(TEXT("Name"), pPtRole_Name); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_Name->aliasID, pPtRole_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(Name / 5).");

	Property* pPtRole_PowerRatio = new Property();
	pPtRole_PowerRatio->name = TEXT("PowerRatio");
	pPtRole_PowerRatio->properUtype = 10;
	pPtRole_PowerRatio->properFlags = 16;
	pPtRole_PowerRatio->aliasID = 8;
	KBVar* pPtRole_PowerRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pPtRole_PowerRatio->pDefaultVal = pPtRole_PowerRatio_defval;
	pPtRoleModule->propertys.Add(TEXT("PowerRatio"), pPtRole_PowerRatio); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_PowerRatio->aliasID, pPtRole_PowerRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(PowerRatio / 10).");

	Property* pPtRole_RoleType = new Property();
	pPtRole_RoleType->name = TEXT("RoleType");
	pPtRole_RoleType->properUtype = 6;
	pPtRole_RoleType->properFlags = 4;
	pPtRole_RoleType->aliasID = 9;
	KBVar* pPtRole_RoleType_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pPtRole_RoleType->pDefaultVal = pPtRole_RoleType_defval;
	pPtRoleModule->propertys.Add(TEXT("RoleType"), pPtRole_RoleType); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_RoleType->aliasID, pPtRole_RoleType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(RoleType / 6).");

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
	pPtRole_SpeedRatio->properUtype = 11;
	pPtRole_SpeedRatio->properFlags = 16;
	pPtRole_SpeedRatio->aliasID = 11;
	KBVar* pPtRole_SpeedRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pPtRole_SpeedRatio->pDefaultVal = pPtRole_SpeedRatio_defval;
	pPtRoleModule->propertys.Add(TEXT("SpeedRatio"), pPtRole_SpeedRatio); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_SpeedRatio->aliasID, pPtRole_SpeedRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(SpeedRatio / 11).");

	TArray<DATATYPE_BASE*> PtRole_OnAnimUpdate_args;
	PtRole_OnAnimUpdate_args.Add(EntityDef::id2datatypes[29]);

	Method* pPtRole_OnAnimUpdate = new Method();
	pPtRole_OnAnimUpdate->name = TEXT("OnAnimUpdate");
	pPtRole_OnAnimUpdate->methodUtype = 16;
	pPtRole_OnAnimUpdate->aliasID = 1;
	pPtRole_OnAnimUpdate->args = PtRole_OnAnimUpdate_args;

	pPtRoleModule->methods.Add(TEXT("OnAnimUpdate"), pPtRole_OnAnimUpdate); 
	pPtRoleModule->useMethodDescrAlias = true;
	pPtRoleModule->idmethods.Add((uint16)pPtRole_OnAnimUpdate->aliasID, pPtRole_OnAnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(OnAnimUpdate / 16).");

	TArray<DATATYPE_BASE*> PtRole_AnimUpdate_args;
	PtRole_AnimUpdate_args.Add(EntityDef::id2datatypes[29]);

	Method* pPtRole_AnimUpdate = new Method();
	pPtRole_AnimUpdate->name = TEXT("AnimUpdate");
	pPtRole_AnimUpdate->methodUtype = 15;
	pPtRole_AnimUpdate->aliasID = -1;
	pPtRole_AnimUpdate->args = PtRole_AnimUpdate_args;

	pPtRoleModule->methods.Add(TEXT("AnimUpdate"), pPtRole_AnimUpdate); 
	pPtRoleModule->cell_methods.Add(TEXT("AnimUpdate"), pPtRole_AnimUpdate);

	pPtRoleModule->idcell_methods.Add(pPtRole_AnimUpdate->methodUtype, pPtRole_AnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(AnimUpdate / 15).");

	TArray<DATATYPE_BASE*> PtRole_Relive_args;

	Method* pPtRole_Relive = new Method();
	pPtRole_Relive->name = TEXT("Relive");
	pPtRole_Relive->methodUtype = 14;
	pPtRole_Relive->aliasID = -1;
	pPtRole_Relive->args = PtRole_Relive_args;

	pPtRoleModule->methods.Add(TEXT("Relive"), pPtRole_Relive); 
	pPtRoleModule->cell_methods.Add(TEXT("Relive"), pPtRole_Relive);

	pPtRoleModule->idcell_methods.Add(pPtRole_Relive->methodUtype, pPtRole_Relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), method(Relive / 14).");

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
	pPtMonster_BaseHP->properUtype = 18;
	pPtMonster_BaseHP->properFlags = 4;
	pPtMonster_BaseHP->aliasID = 4;
	KBVar* pPtMonster_BaseHP_defval = new KBVar((int16)FCString::Atoi64(TEXT("500")));
	pPtMonster_BaseHP->pDefaultVal = pPtMonster_BaseHP_defval;
	pPtMonsterModule->propertys.Add(TEXT("BaseHP"), pPtMonster_BaseHP); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_BaseHP->aliasID, pPtMonster_BaseHP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(BaseHP / 18).");

	Property* pPtMonster_Defense = new Property();
	pPtMonster_Defense->name = TEXT("Defense");
	pPtMonster_Defense->properUtype = 20;
	pPtMonster_Defense->properFlags = 16;
	pPtMonster_Defense->aliasID = 5;
	KBVar* pPtMonster_Defense_defval = new KBVar((int16)FCString::Atoi64(TEXT("10")));
	pPtMonster_Defense->pDefaultVal = pPtMonster_Defense_defval;
	pPtMonsterModule->propertys.Add(TEXT("Defense"), pPtMonster_Defense); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_Defense->aliasID, pPtMonster_Defense);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(Defense / 20).");

	Property* pPtMonster_HP = new Property();
	pPtMonster_HP->name = TEXT("HP");
	pPtMonster_HP->properUtype = 19;
	pPtMonster_HP->properFlags = 4;
	pPtMonster_HP->aliasID = 6;
	KBVar* pPtMonster_HP_defval = new KBVar((int16)FCString::Atoi64(TEXT("500")));
	pPtMonster_HP->pDefaultVal = pPtMonster_HP_defval;
	pPtMonsterModule->propertys.Add(TEXT("HP"), pPtMonster_HP); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_HP->aliasID, pPtMonster_HP);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(HP / 19).");

	Property* pPtMonster_Name = new Property();
	pPtMonster_Name->name = TEXT("Name");
	pPtMonster_Name->properUtype = 16;
	pPtMonster_Name->properFlags = 4;
	pPtMonster_Name->aliasID = 7;
	KBVar* pPtMonster_Name_defval = new KBVar(FString());
	pPtMonster_Name->pDefaultVal = pPtMonster_Name_defval;
	pPtMonsterModule->propertys.Add(TEXT("Name"), pPtMonster_Name); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_Name->aliasID, pPtMonster_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(Name / 16).");

	Property* pPtMonster_PowerRatio = new Property();
	pPtMonster_PowerRatio->name = TEXT("PowerRatio");
	pPtMonster_PowerRatio->properUtype = 21;
	pPtMonster_PowerRatio->properFlags = 16;
	pPtMonster_PowerRatio->aliasID = 8;
	KBVar* pPtMonster_PowerRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pPtMonster_PowerRatio->pDefaultVal = pPtMonster_PowerRatio_defval;
	pPtMonsterModule->propertys.Add(TEXT("PowerRatio"), pPtMonster_PowerRatio); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_PowerRatio->aliasID, pPtMonster_PowerRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(PowerRatio / 21).");

	Property* pPtMonster_RoleType = new Property();
	pPtMonster_RoleType->name = TEXT("RoleType");
	pPtMonster_RoleType->properUtype = 17;
	pPtMonster_RoleType->properFlags = 4;
	pPtMonster_RoleType->aliasID = 9;
	KBVar* pPtMonster_RoleType_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pPtMonster_RoleType->pDefaultVal = pPtMonster_RoleType_defval;
	pPtMonsterModule->propertys.Add(TEXT("RoleType"), pPtMonster_RoleType); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_RoleType->aliasID, pPtMonster_RoleType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(RoleType / 17).");

	Property* pPtMonster_SpeedRatio = new Property();
	pPtMonster_SpeedRatio->name = TEXT("SpeedRatio");
	pPtMonster_SpeedRatio->properUtype = 22;
	pPtMonster_SpeedRatio->properFlags = 16;
	pPtMonster_SpeedRatio->aliasID = 10;
	KBVar* pPtMonster_SpeedRatio_defval = new KBVar(FCString::Atof(TEXT("1.0")));
	pPtMonster_SpeedRatio->pDefaultVal = pPtMonster_SpeedRatio_defval;
	pPtMonsterModule->propertys.Add(TEXT("SpeedRatio"), pPtMonster_SpeedRatio); 

	pPtMonsterModule->usePropertyDescrAlias = true;
	pPtMonsterModule->idpropertys.Add((uint16)pPtMonster_SpeedRatio->aliasID, pPtMonster_SpeedRatio);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), property(SpeedRatio / 22).");

	TArray<DATATYPE_BASE*> PtMonster_OnAnimUpdate_args;
	PtMonster_OnAnimUpdate_args.Add(EntityDef::id2datatypes[29]);

	Method* pPtMonster_OnAnimUpdate = new Method();
	pPtMonster_OnAnimUpdate->name = TEXT("OnAnimUpdate");
	pPtMonster_OnAnimUpdate->methodUtype = 19;
	pPtMonster_OnAnimUpdate->aliasID = 1;
	pPtMonster_OnAnimUpdate->args = PtMonster_OnAnimUpdate_args;

	pPtMonsterModule->methods.Add(TEXT("OnAnimUpdate"), pPtMonster_OnAnimUpdate); 
	pPtMonsterModule->useMethodDescrAlias = true;
	pPtMonsterModule->idmethods.Add((uint16)pPtMonster_OnAnimUpdate->aliasID, pPtMonster_OnAnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), method(OnAnimUpdate / 19).");

	TArray<DATATYPE_BASE*> PtMonster_AnimUpdate_args;
	PtMonster_AnimUpdate_args.Add(EntityDef::id2datatypes[29]);

	Method* pPtMonster_AnimUpdate = new Method();
	pPtMonster_AnimUpdate->name = TEXT("AnimUpdate");
	pPtMonster_AnimUpdate->methodUtype = 18;
	pPtMonster_AnimUpdate->aliasID = -1;
	pPtMonster_AnimUpdate->args = PtMonster_AnimUpdate_args;

	pPtMonsterModule->methods.Add(TEXT("AnimUpdate"), pPtMonster_AnimUpdate); 
	pPtMonsterModule->cell_methods.Add(TEXT("AnimUpdate"), pPtMonster_AnimUpdate);

	pPtMonsterModule->idcell_methods.Add(pPtMonster_AnimUpdate->methodUtype, pPtMonster_AnimUpdate);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), method(AnimUpdate / 18).");

	TArray<DATATYPE_BASE*> PtMonster_Relive_args;

	Method* pPtMonster_Relive = new Method();
	pPtMonster_Relive->name = TEXT("Relive");
	pPtMonster_Relive->methodUtype = 17;
	pPtMonster_Relive->aliasID = -1;
	pPtMonster_Relive->args = PtMonster_Relive_args;

	pPtMonsterModule->methods.Add(TEXT("Relive"), pPtMonster_Relive); 
	pPtMonsterModule->cell_methods.Add(TEXT("Relive"), pPtMonster_Relive);

	pPtMonsterModule->idcell_methods.Add(pPtMonster_Relive->methodUtype, pPtMonster_Relive);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtMonster), method(Relive / 17).");

}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("BOOL");
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
		FString typeName = TEXT("INT32");
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
		FString typeName = TEXT("ROLE_DATA");
		DATATYPE_ROLE_DATA* pDatatype = new DATATYPE_ROLE_DATA();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 23;
		FString typeName = TEXT("ROLE_INFO");
		DATATYPE_ROLE_INFO* pDatatype = new DATATYPE_ROLE_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 24;
		FString typeName = TEXT("ROLE_LIST");
		DATATYPE_ROLE_LIST* pDatatype = new DATATYPE_ROLE_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 26;
		FString typeName = TEXT("ROOM_INFO");
		DATATYPE_ROOM_INFO* pDatatype = new DATATYPE_ROOM_INFO();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 27;
		FString typeName = TEXT("ROOM_LIST");
		DATATYPE_ROOM_LIST* pDatatype = new DATATYPE_ROOM_LIST();
		EntityDef::datatypes.Add(typeName, (DATATYPE_BASE*)pDatatype);
		EntityDef::id2datatypes.Add(utype, EntityDef::datatypes[typeName]);
		EntityDef::datatype2id.Add(typeName, utype);
	}

	{
		uint16 utype = 29;
		FString typeName = TEXT("ANIM_INFO");
		DATATYPE_ANIM_INFO* pDatatype = new DATATYPE_ANIM_INFO();
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