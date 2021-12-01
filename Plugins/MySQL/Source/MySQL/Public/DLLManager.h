// Copyright 2021, Athian Games. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "PlatformFeatures.h"
#include "MySQLBPLibrary.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

#if PLATFORM_WINDOWS
	#include "Windows/WindowsPlatformProcess.h"
	#include <map>
	#include <string>
	#include <vector>

using namespace std;

static class DLLManager
{
private:


	static bool ImportMethodOpenFileDialogue();
	static bool ImportMethodSetConnectionProperties();
	static bool ImportMethodUpdateDataFromQuery();
	static bool ImportMethodSelectDataFromQuery();
	static bool ImportMethodCloseConnection();

	static TArray<FString> GetSplitStringArray(FString Input, FString Pattern);

public:

	/**
	* Loads DLL from the given name.
	* @param  DLLName  The DLL to load.
	* @returns true if the DLL is successfully loaded.
	*/
	static bool LoadDLL(FString DLLName);

	/**
	* UnLoads the currently loaded DLL.
	*/
	static void UnLoadDLL();

	/**
	* Opens the File Open Dialogue Window and returns the array of filenames selected for openiong.
	*
	* @param DialogueTitle  The Title that appears in the titlebar of the File Open Dialogue window.
	* @param FileTypes  The allowed FileTypes for the File Open Dialogue window.
	* @param multiselect  If user can select multiple files.
	*/
	static TArray<FString> GetOpenFileDialogue(FString DialogueTitle, FString FileTypes, bool multiselect);


	static bool SetConnectionProperties(FString Server, FString DBName, FString UserID, FString Password, TMap<FString, FString> ExtraParams,
		FString& ErrorMessage);

	static bool UpdateDataFromQuery(FString Query, FString& ErrorMessage);
	static bool SelectDataFromQuery(FString Query, FString& ErrorMessage, TArray<FMySQLDataTable>& ResultByColumn, TArray<FMySQLDataRow>& ResultByRow);

	static void CloseConnection();


};

#endif

