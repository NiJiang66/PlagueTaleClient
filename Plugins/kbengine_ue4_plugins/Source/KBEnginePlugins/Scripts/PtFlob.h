#pragma once
#include "Engine/KBECommon.h"
#include "Engine/PtFlobBase.h"

namespace KBEngine
{
	class PtFlob : public PtFlobBase
	{
	public:
		PtFlob();
		virtual ~PtFlob();

	public:
		virtual void __init__() override;
		virtual void onDestroy() override;

	};

}