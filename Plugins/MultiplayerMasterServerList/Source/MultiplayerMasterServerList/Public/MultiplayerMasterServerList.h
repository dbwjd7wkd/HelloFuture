// Multiplayer Master Server Plugin Copyright (C) 2020 MeoPlay <contact@meoplay.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMultiplayerMasterServerListModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
