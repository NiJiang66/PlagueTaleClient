#pragma once
#include "Engine/KBECommon.h"
#include "Engine/PtRoleBase.h"

namespace KBEngine
{
	class PtRole : public PtRoleBase
	{
	public:
		PtRole();
		virtual ~PtRole();

	public:
		virtual void __init__()override;
		virtual void onDestroy()override;



	};


}