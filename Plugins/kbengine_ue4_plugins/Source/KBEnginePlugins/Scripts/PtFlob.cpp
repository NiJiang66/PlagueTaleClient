#include "PtFlob.h"
#include "Engine/KBEvent.h"


KBEngine::PtFlob::PtFlob()
{

}

KBEngine::PtFlob::~PtFlob()
{

}

void KBEngine::PtFlob::__init__()
{

}

void KBEngine::PtFlob::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

