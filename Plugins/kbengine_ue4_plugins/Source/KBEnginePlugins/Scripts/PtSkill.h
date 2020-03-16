#pragma once
#include "Engine/KBECommon.h"
#include "Engine/PtSkillBase.h"

namespace KBEngine
{
	class PtSkill : public PtSkillBase
	{
	public:
		PtSkill();
		virtual ~PtSkill();

	public:
		virtual void __init__() override;
		virtual void onDestroy() override;

	};

}