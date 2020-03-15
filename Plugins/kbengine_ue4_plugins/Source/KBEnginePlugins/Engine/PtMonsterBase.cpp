#include "PtMonsterBase.h"
#include "KBVar.h"
#include "EntityDef.h"
#include "ScriptModule.h"
#include "Property.h"
#include "Method.h"
#include "DataTypes.h"
#include "CustomDataTypes.h"
#include "MemoryStream.h"
#include "EntityComponent.h"

namespace KBEngine
{



void PtMonsterBase::onComponentsEnterworld()
{
}

void PtMonsterBase::onComponentsLeaveworld()
{
}

void PtMonsterBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_PtMonsterBase(id(), className());
}

void PtMonsterBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_PtMonsterBase(id(), className());
}

void PtMonsterBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* PtMonsterBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* PtMonsterBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void PtMonsterBase::onRemoteMethodCall(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("PtMonster");
	uint16 methodUtype = 0;
	uint16 componentPropertyUType = 0;

	if (sm->usePropertyDescrAlias)
	{
		componentPropertyUType = stream.readUint8();
	}
	else
	{
		componentPropertyUType = stream.readUint16();
	}

	if (sm->useMethodDescrAlias)
	{
		methodUtype = stream.read<uint8>();
	}
	else
	{
		methodUtype = stream.read<uint16>();
	}

	if(componentPropertyUType > 0)
	{
		KBE_ASSERT(false);

		return;
	}

	Method* pMethod = sm->idmethods[methodUtype];

	switch(pMethod->methodUtype)
	{
		case 25:
		{
			ANIM_INFO OnAnimUpdate_arg1;
			((DATATYPE_ANIM_INFO*)pMethod->args[0])->createFromStreamEx(stream, OnAnimUpdate_arg1);
			OnAnimUpdate(OnAnimUpdate_arg1);
			break;
		}
		case 23:
		{
			OnAttack();
			break;
		}
		default:
			break;
	};
}

void PtMonsterBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("PtMonster");

	while(stream.length() > 0)
	{
		uint16 componentPropertyUType = 0;
		uint16 properUtype = 0;

		if (sm->usePropertyDescrAlias)
		{
			componentPropertyUType = stream.readUint8();
			properUtype = stream.read<uint8>();
		}
		else
		{
			componentPropertyUType = stream.readUint16();
			properUtype = stream.read<uint16>();
		}

		if(componentPropertyUType > 0)
		{
			KBE_ASSERT(false);

			return;
		}

		Property* pProp = sm->idpropertys[properUtype];

		switch(pProp->properUtype)
		{
			case 19:
			{
				int16 oldval_BaseHP = BaseHP;
				BaseHP = stream.readInt16();

				if(pProp->isBase())
				{
					if(inited())
						onBaseHPChanged(oldval_BaseHP);
				}
				else
				{
					if(inWorld())
						onBaseHPChanged(oldval_BaseHP);
				}

				break;
			}
			case 21:
			{
				int16 oldval_Defense = Defense;
				Defense = stream.readInt16();

				if(pProp->isBase())
				{
					if(inited())
						onDefenseChanged(oldval_Defense);
				}
				else
				{
					if(inWorld())
						onDefenseChanged(oldval_Defense);
				}

				break;
			}
			case 20:
			{
				int16 oldval_HP = HP;
				HP = stream.readInt16();

				if(pProp->isBase())
				{
					if(inited())
						onHPChanged(oldval_HP);
				}
				else
				{
					if(inWorld())
						onHPChanged(oldval_HP);
				}

				break;
			}
			case 17:
			{
				FString oldval_Name = Name;
				Name = stream.readUnicode();

				if(pProp->isBase())
				{
					if(inited())
						onNameChanged(oldval_Name);
				}
				else
				{
					if(inWorld())
						onNameChanged(oldval_Name);
				}

				break;
			}
			case 22:
			{
				float oldval_PowerRatio = PowerRatio;
				PowerRatio = stream.readFloat();

				if(pProp->isBase())
				{
					if(inited())
						onPowerRatioChanged(oldval_PowerRatio);
				}
				else
				{
					if(inWorld())
						onPowerRatioChanged(oldval_PowerRatio);
				}

				break;
			}
			case 18:
			{
				uint8 oldval_RoleType = RoleType;
				RoleType = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onRoleTypeChanged(oldval_RoleType);
				}
				else
				{
					if(inWorld())
						onRoleTypeChanged(oldval_RoleType);
				}

				break;
			}
			case 23:
			{
				float oldval_SpeedRatio = SpeedRatio;
				SpeedRatio = stream.readFloat();

				if(pProp->isBase())
				{
					if(inited())
						onSpeedRatioChanged(oldval_SpeedRatio);
				}
				else
				{
					if(inWorld())
						onSpeedRatioChanged(oldval_SpeedRatio);
				}

				break;
			}
			case 40001:
			{
				FVector oldval_direction = direction;
				direction = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onDirectionChanged(oldval_direction);
				}
				else
				{
					if(inWorld())
						onDirectionChanged(oldval_direction);
				}

				break;
			}
			case 40000:
			{
				FVector oldval_position = position;
				position = stream.readVector3();

				if(pProp->isBase())
				{
					if(inited())
						onPositionChanged(oldval_position);
				}
				else
				{
					if(inWorld())
						onPositionChanged(oldval_position);
				}

				break;
			}
			case 40002:
			{
				stream.readUint32();
				break;
			}
			default:
				break;
		};
	}
}

void PtMonsterBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["PtMonster"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	int16 oldval_BaseHP = BaseHP;
	Property* pProp_BaseHP = pdatas[4];
	if(pProp_BaseHP->isBase())
	{
		if(inited() && !inWorld())
			onBaseHPChanged(oldval_BaseHP);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_BaseHP->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onBaseHPChanged(oldval_BaseHP);
			}
		}
	}

	int16 oldval_Defense = Defense;
	Property* pProp_Defense = pdatas[5];
	if(pProp_Defense->isBase())
	{
		if(inited() && !inWorld())
			onDefenseChanged(oldval_Defense);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_Defense->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDefenseChanged(oldval_Defense);
			}
		}
	}

	int16 oldval_HP = HP;
	Property* pProp_HP = pdatas[6];
	if(pProp_HP->isBase())
	{
		if(inited() && !inWorld())
			onHPChanged(oldval_HP);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_HP->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onHPChanged(oldval_HP);
			}
		}
	}

	FString oldval_Name = Name;
	Property* pProp_Name = pdatas[7];
	if(pProp_Name->isBase())
	{
		if(inited() && !inWorld())
			onNameChanged(oldval_Name);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_Name->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onNameChanged(oldval_Name);
			}
		}
	}

	float oldval_PowerRatio = PowerRatio;
	Property* pProp_PowerRatio = pdatas[8];
	if(pProp_PowerRatio->isBase())
	{
		if(inited() && !inWorld())
			onPowerRatioChanged(oldval_PowerRatio);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_PowerRatio->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onPowerRatioChanged(oldval_PowerRatio);
			}
		}
	}

	uint8 oldval_RoleType = RoleType;
	Property* pProp_RoleType = pdatas[9];
	if(pProp_RoleType->isBase())
	{
		if(inited() && !inWorld())
			onRoleTypeChanged(oldval_RoleType);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_RoleType->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onRoleTypeChanged(oldval_RoleType);
			}
		}
	}

	float oldval_SpeedRatio = SpeedRatio;
	Property* pProp_SpeedRatio = pdatas[10];
	if(pProp_SpeedRatio->isBase())
	{
		if(inited() && !inWorld())
			onSpeedRatioChanged(oldval_SpeedRatio);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_SpeedRatio->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onSpeedRatioChanged(oldval_SpeedRatio);
			}
		}
	}

	FVector oldval_direction = direction;
	Property* pProp_direction = pdatas[2];
	if(pProp_direction->isBase())
	{
		if(inited() && !inWorld())
			onDirectionChanged(oldval_direction);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_direction->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onDirectionChanged(oldval_direction);
			}
		}
	}

	FVector oldval_position = position;
	Property* pProp_position = pdatas[1];
	if(pProp_position->isBase())
	{
		if(inited() && !inWorld())
			onPositionChanged(oldval_position);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_position->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onPositionChanged(oldval_position);
			}
		}
	}

}

PtMonsterBase::PtMonsterBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	BaseHP((int16)FCString::Atoi64(TEXT("500"))),
	Defense((int16)FCString::Atoi64(TEXT("10"))),
	HP((int16)FCString::Atoi64(TEXT("500"))),
	Name(TEXT("")),
	PowerRatio(FCString::Atof(TEXT("1.0"))),
	RoleType((uint8)FCString::Atoi64(TEXT("0"))),
	SpeedRatio(FCString::Atof(TEXT("1.0")))
{
}

PtMonsterBase::~PtMonsterBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void PtMonsterBase::attachComponents()
{
}

void PtMonsterBase::detachComponents()
{
}

}