#pragma once
#include "Engine/KBECommon.h"
#include "Engine/PtMonsterBase.h"

namespace KBEngine
{
	class PtMonster : public PtMonsterBase
	{
	public:
		PtMonster();
		virtual ~PtMonster();

	public:
		virtual void __init__() override;
		virtual void onDestroy() override;

		virtual void OnAnimUpdate(const ANIM_INFO& arg1) override;

		virtual void onBaseHPChanged(int16 oldValue) override;
		//virtual void onDefenseChanged(int16 oldValue) override;
		virtual void onHPChanged(int16 oldValue) override;
		//virtual void onPowerRatioChanged(float oldValue) override;
	};


}