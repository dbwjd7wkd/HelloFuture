// Multiplayer Master Server Plugin Copyright (C) 2020 MeoPlay <contact@meoplay.com> All Rights Reserved.

#include "MultiplayerMasterServerList.h"

#define LOCTEXT_NAMESPACE "FMultiplayerMasterServerListModule"

void FMultiplayerMasterServerListModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMultiplayerMasterServerListModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMultiplayerMasterServerListModule, MultiplayerMasterServerList)