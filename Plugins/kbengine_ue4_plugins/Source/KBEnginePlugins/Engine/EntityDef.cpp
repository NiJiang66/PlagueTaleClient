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
	pPtAccount_OnCreateRoleResult->methodUtype = 6;
	pPtAccount_OnCreateRoleResult->aliasID = 1;
	pPtAccount_OnCreateRoleResult->args = PtAccount_OnCreateRoleResult_args;

	pPtAccountModule->methods.Add(TEXT("OnCreateRoleResult"), pPtAccount_OnCreateRoleResult); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnCreateRoleResult->aliasID, pPtAccount_OnCreateRoleResult);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnCreateRoleResult / 6).");

	TArray<DATATYPE_BASE*> PtAccount_OnRemoveRole_args;
	PtAccount_OnRemoveRole_args.Add(EntityDef::id2datatypes[5]);

	Method* pPtAccount_OnRemoveRole = new Method();
	pPtAccount_OnRemoveRole->name = TEXT("OnRemoveRole");
	pPtAccount_OnRemoveRole->methodUtype = 7;
	pPtAccount_OnRemoveRole->aliasID = 2;
	pPtAccount_OnRemoveRole->args = PtAccount_OnRemoveRole_args;

	pPtAccountModule->methods.Add(TEXT("OnRemoveRole"), pPtAccount_OnRemoveRole); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnRemoveRole->aliasID, pPtAccount_OnRemoveRole);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnRemoveRole / 7).");

	TArray<DATATYPE_BASE*> PtAccount_OnReqRoleList_args;
	PtAccount_OnReqRoleList_args.Add(EntityDef::id2datatypes[24]);

	Method* pPtAccount_OnReqRoleList = new Method();
	pPtAccount_OnReqRoleList->name = TEXT("OnReqRoleList");
	pPtAccount_OnReqRoleList->methodUtype = 5;
	pPtAccount_OnReqRoleList->aliasID = 3;
	pPtAccount_OnReqRoleList->args = PtAccount_OnReqRoleList_args;

	pPtAccountModule->methods.Add(TEXT("OnReqRoleList"), pPtAccount_OnReqRoleList); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnReqRoleList->aliasID, pPtAccount_OnReqRoleList);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnReqRoleList / 5).");

	TArray<DATATYPE_BASE*> PtAccount_OnSelectRoleGame_args;
	PtAccount_OnSelectRoleGame_args.Add(EntityDef::id2datatypes[2]);
	PtAccount_OnSelectRoleGame_args.Add(EntityDef::id2datatypes[5]);

	Method* pPtAccount_OnSelectRoleGame = new Method();
	pPtAccount_OnSelectRoleGame->name = TEXT("OnSelectRoleGame");
	pPtAccount_OnSelectRoleGame->methodUtype = 8;
	pPtAccount_OnSelectRoleGame->aliasID = 4;
	pPtAccount_OnSelectRoleGame->args = PtAccount_OnSelectRoleGame_args;

	pPtAccountModule->methods.Add(TEXT("OnSelectRoleGame"), pPtAccount_OnSelectRoleGame); 
	pPtAccountModule->useMethodDescrAlias = true;
	pPtAccountModule->idmethods.Add((uint16)pPtAccount_OnSelectRoleGame->aliasID, pPtAccount_OnSelectRoleGame);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtAccount), method(OnSelectRoleGame / 8).");

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

	Property* pPtRole_Name = new Property();
	pPtRole_Name->name = TEXT("Name");
	pPtRole_Name->properUtype = 3;
	pPtRole_Name->properFlags = 4;
	pPtRole_Name->aliasID = 4;
	KBVar* pPtRole_Name_defval = new KBVar(FString());
	pPtRole_Name->pDefaultVal = pPtRole_Name_defval;
	pPtRoleModule->propertys.Add(TEXT("Name"), pPtRole_Name); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_Name->aliasID, pPtRole_Name);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(Name / 3).");

	Property* pPtRole_RoleType = new Property();
	pPtRole_RoleType->name = TEXT("RoleType");
	pPtRole_RoleType->properUtype = 4;
	pPtRole_RoleType->properFlags = 4;
	pPtRole_RoleType->aliasID = 5;
	KBVar* pPtRole_RoleType_defval = new KBVar((uint8)FCString::Atoi64(TEXT("")));
	pPtRole_RoleType->pDefaultVal = pPtRole_RoleType_defval;
	pPtRoleModule->propertys.Add(TEXT("RoleType"), pPtRole_RoleType); 

	pPtRoleModule->usePropertyDescrAlias = true;
	pPtRoleModule->idpropertys.Add((uint16)pPtRole_RoleType->aliasID, pPtRole_RoleType);

	//DEBUG_MSG("EntityDef::initScriptModules: add(PtRole), property(RoleType / 4).");

	pPtRoleModule->useMethodDescrAlias = true;
}

void EntityDef::initDefTypes()
{
	{
		uint16 utype = 2;
		FString typeName = TEXT("UINT8");
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

	for(auto& Elem : EntityDef::datatypes)
	{
		if(Elem.Value)
		{
			Elem.Value->bind();
		}
	}
}


}