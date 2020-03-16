#include "PtSkillBase.h"
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



void PtSkillBase::onComponentsEnterworld()
{
}

void PtSkillBase::onComponentsLeaveworld()
{
}

void PtSkillBase::onGetBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	pBaseEntityCall = new EntityBaseEntityCall_PtSkillBase(id(), className());
}

void PtSkillBase::onGetCell()
{
	if(pCellEntityCall)
		delete pCellEntityCall;

	pCellEntityCall = new EntityCellEntityCall_PtSkillBase(id(), className());
}

void PtSkillBase::onLoseCell()
{
	delete pCellEntityCall;
	pCellEntityCall = NULL;
}

EntityCall* PtSkillBase::getBaseEntityCall()
{
	return pBaseEntityCall;
}

EntityCall* PtSkillBase::getCellEntityCall()
{
	return pCellEntityCall;
}

void PtSkillBase::onRemoteMethodCall(MemoryStream& stream)
{
}

void PtSkillBase::onUpdatePropertys(MemoryStream& stream)
{
	ScriptModule* sm = *EntityDef::moduledefs.Find("PtSkill");

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
			case 40:
			{
				uint8 oldval_SkillId = SkillId;
				SkillId = stream.readUint8();

				if(pProp->isBase())
				{
					if(inited())
						onSkillIdChanged(oldval_SkillId);
				}
				else
				{
					if(inWorld())
						onSkillIdChanged(oldval_SkillId);
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

void PtSkillBase::callPropertysSetMethods()
{
	ScriptModule* sm = EntityDef::moduledefs["PtSkill"];
	TMap<uint16, Property*>& pdatas = sm->idpropertys;

	uint8 oldval_SkillId = SkillId;
	Property* pProp_SkillId = pdatas[4];
	if(pProp_SkillId->isBase())
	{
		if(inited() && !inWorld())
			onSkillIdChanged(oldval_SkillId);
	}
	else
	{
		if(inWorld())
		{
			if(pProp_SkillId->isOwnerOnly() && !isPlayer())
			{
			}
			else
			{
				onSkillIdChanged(oldval_SkillId);
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

PtSkillBase::PtSkillBase():
	Entity(),
	pBaseEntityCall(NULL),
	pCellEntityCall(NULL),
	SkillId((uint8)FCString::Atoi64(TEXT("0")))
{
}

PtSkillBase::~PtSkillBase()
{
	if(pBaseEntityCall)
		delete pBaseEntityCall;

	if(pCellEntityCall)
		delete pCellEntityCall;

}

void PtSkillBase::attachComponents()
{
}

void PtSkillBase::detachComponents()
{
}

}