#include "PtRole.h"
#include "Engine/KBEvent.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtCommon.h"

KBEngine::PtRole::PtRole()
{

}

KBEngine::PtRole::~PtRole()
{

}

void KBEngine::PtRole::__init__()
{
	//触发登录成功事件
	//UKBEventData_onLoginSuccessfully* EventData = NewObject<UKBEventData_onLoginSuccessfully>();
	//EventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	//EventData->entity_id = id();
	//KBENGINE_EVENT_FIRE("onLoginSuccessfully", EventData);//在APtStartGameMode::InstallEvents()里注册

	//PtH::Debug() << "PtAccount::__init__ and Fire 'onLoginSuccessfully' Event" << PtH::Endl();
}

void KBEngine::PtRole::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

