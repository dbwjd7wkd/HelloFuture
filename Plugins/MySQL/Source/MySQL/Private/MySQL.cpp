// Copyright 2021, Athian Games. All Rights Reserved. 

#include "MySQL.h"

#define LOCTEXT_NAMESPACE "FMySQLModule"

void FMySQLModule::CopyDLL(FString DLLName)
{
	FString Pluginpath = IPluginManager::Get().FindPlugin(TEXT("MySQL"))->GetBaseDir();
	FString PluginDLLPath = FPaths::Combine(*Pluginpath, TEXT("Binaries"), TEXT("Win64"), DLLName);

	FString ProjectDirectory = FPaths::ProjectDir();
	FString ProjectDLLDirectory = FPaths::Combine(*ProjectDirectory, TEXT("Binaries"), TEXT("Win64"));

	FString ProjectDLLPath = FPaths::Combine(*ProjectDLLDirectory, DLLName);

	if (!FPaths::DirectoryExists(*ProjectDLLDirectory))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*ProjectDLLDirectory);
	}

	if (FPaths::FileExists(PluginDLLPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CopyFile(*ProjectDLLPath, *PluginDLLPath);
	}
	else if (!FPaths::FileExists(PluginDLLPath) && FPaths::FileExists(ProjectDLLPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CopyFile(*PluginDLLPath, *ProjectDLLPath);
	}

}

void FMySQLModule::StartupModule()
{
	CopyDLL(TEXT("mysqlcppconn-9-vs14.dll"));
	CopyDLL(TEXT("FileBrowser.dll"));
	CopyDLL(TEXT("MySQLLibrary.dll"));

}


void FMySQLModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMySQLModule, MySQL)