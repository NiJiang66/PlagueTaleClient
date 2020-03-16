#include "PtSkill.h"
#include "Engine/KBEvent.h"

KBEngine::PtSkill::PtSkill()
{

}

KBEngine::PtSkill::~PtSkill()
{

}

void KBEngine::PtSkill::__init__()
{

}

void KBEngine::PtSkill::onDestroy()
{
	// 注销注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}
