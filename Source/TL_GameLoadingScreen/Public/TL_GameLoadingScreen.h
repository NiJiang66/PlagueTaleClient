#pragma once
#include "ModuleInterface.h"


/** Module interface for this game's loading screens */
class ITL_GameLoadingScreenModule : public IModuleInterface
{
public:
	/** Kicks off the loading screen for in game loading (not startup) */
	virtual void StartInGameLoadingScreen() = 0;
};
