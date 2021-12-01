// Copyright 2021, Athian Games. All Rights Reserved. 

#include "DLLManager.h"
#include "Interfaces/IPluginManager.h"

#if PLATFORM_WINDOWS

static void *v_dllHandle;

typedef char*(*_OpenFileDialogue)(char* DialogueTitle, char* FileTypes, bool multiselect);
typedef bool(*_SetConnectionProperties)(char* Server, char* DBName, char* UserID, char* Password, char* EparamMap, const char*& ErrorMessage);
typedef bool(*_UpdateDataFromQuery)(char* Query, const char*& ErrorMessage);
typedef bool(*_SelectDataFromQuery)(char* Query, char* TempDirectory, const char*& ErrorMessage);
typedef void(*_CloseConnection)();


_OpenFileDialogue m_OpenFileDialogueFromDll;
_SetConnectionProperties m_SetConnectionPropertiesFromDll;
_UpdateDataFromQuery m_UpdateDataFromQueryFromDll;
_SelectDataFromQuery m_SelectDataFromQueryFromDll;
_CloseConnection m_CloseConnectionFromDll;

bool DLLManager::LoadDLL(FString DLLName)
{
	FString DllPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Binaries/Win64"), DLLName);

	if (FPaths::FileExists(DllPath))
	{
		v_dllHandle = FPlatformProcess::GetDllHandle(*DllPath);
		if (v_dllHandle != NULL)
		{
			return true;
		}
	}
	return false;
}

void DLLManager::UnLoadDLL()
{
	if (v_dllHandle != NULL)
	{
		FPlatformProcess::FreeDllHandle(m_OpenFileDialogueFromDll);
		FPlatformProcess::FreeDllHandle(m_SetConnectionPropertiesFromDll);
		FPlatformProcess::FreeDllHandle(m_UpdateDataFromQueryFromDll);
		FPlatformProcess::FreeDllHandle(m_SelectDataFromQueryFromDll);
		FPlatformProcess::FreeDllHandle(m_CloseConnectionFromDll);

		FPlatformProcess::FreeDllHandle(v_dllHandle);
		v_dllHandle = NULL;
		m_OpenFileDialogueFromDll = NULL;
		m_SetConnectionPropertiesFromDll = NULL;

	}
}


TArray<FString> DLLManager::GetSplitStringArray(FString Input, FString Pattern)
{

	TArray<FString> Results;

	FString Base;
	FString Left;
	FString Remaining;

	if (Input.Split(Pattern, &Base, &Remaining))
	{
		Results.Add(Base);

		while (Remaining != "")
		{
			if (Remaining.Split(Pattern, &Left, &Remaining))
			{
				Results.Add(Left);
			}
			else
			{
				Results.Add(Remaining);
				Remaining = "";
			}
		}

	}
	else
	{
		Results.Add(Input);

	}

	return Results;

}

bool DLLManager::ImportMethodCloseConnection()
{
	if (v_dllHandle != NULL)
	{
		m_CloseConnectionFromDll = NULL;
		FString procName = "CloseConnection";
		m_CloseConnectionFromDll = (_CloseConnection)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CloseConnectionFromDll != NULL)
		{
			return true;
		}
	}
	return false;
}

bool DLLManager::ImportMethodOpenFileDialogue()
{
	if (v_dllHandle != NULL)
	{
		m_OpenFileDialogueFromDll = NULL;
		FString procName = "OpenFileDialogue";
		m_OpenFileDialogueFromDll = (_OpenFileDialogue)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_OpenFileDialogueFromDll != NULL)
		{
			return true;
		}
	}
	return false;
}

TArray<FString> DLLManager::GetOpenFileDialogue(FString DialogueTitle, FString FileTypes, bool multiselect)
{
	TArray<FString> OpenedFiles;
	if (ImportMethodOpenFileDialogue())
	{

		char* title = TCHAR_TO_ANSI(*DialogueTitle);
		char* filetypes = TCHAR_TO_ANSI(*FileTypes);

		char* openedfilename = m_OpenFileDialogueFromDll(title, filetypes, multiselect);

		FString RString = FString(openedfilename);
		if (!RString.IsEmpty())
		{
			FString LString;
			while (!RString.IsEmpty())
			{
				FString NString = RString;
				RString.Empty();
				if (NString.Contains(","))
				{
					NString.Split(",", &LString, &RString, ESearchCase::CaseSensitive);
				}
				else
				{
					LString = NString;
				}
				if (FPaths::FileExists(LString))
				{
					OpenedFiles.Add(LString);
				}
			}


		}
	}

	return OpenedFiles;
}


bool DLLManager::ImportMethodSetConnectionProperties()
{
	if (v_dllHandle != NULL)
	{
		m_SetConnectionPropertiesFromDll = NULL;
		FString procName = "SetConnectionProperties";
		m_SetConnectionPropertiesFromDll = (_SetConnectionProperties)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_SetConnectionPropertiesFromDll != NULL)
		{
			return true;
		}
	}
	return false;
}

bool DLLManager::ImportMethodUpdateDataFromQuery()
{
	if (v_dllHandle != NULL)
	{
		m_UpdateDataFromQueryFromDll = NULL;
		FString procName = "UpdateDataFromQuery";
		m_UpdateDataFromQueryFromDll = (_UpdateDataFromQuery)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_UpdateDataFromQueryFromDll != NULL)
		{
			return true;
		}
	}
	return false;
}


bool DLLManager::ImportMethodSelectDataFromQuery()
{
	if (v_dllHandle != NULL)
	{
		m_SelectDataFromQueryFromDll = NULL;
		FString procName = "SelectDataFromQuery";
		m_SelectDataFromQueryFromDll = (_SelectDataFromQuery)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_SelectDataFromQueryFromDll != NULL)
		{
			return true;
		}
	}
	return false;
}


void DLLManager::CloseConnection()
{
	if (ImportMethodCloseConnection())
	{
		m_CloseConnectionFromDll();
	}
}



bool DLLManager::SetConnectionProperties(FString Server, FString DBName, FString UserID, FString Password, TMap<FString, FString> ExtraParams,
	FString& ErrorMessage)
{
	if (ImportMethodSetConnectionProperties())
	{
		string titlestring(TCHAR_TO_UTF8(*Server));
		char* title = _strdup(titlestring.c_str());

		string dbnamestring(TCHAR_TO_UTF8(*DBName));
		char* dbname = _strdup(dbnamestring.c_str());

		string useridstring(TCHAR_TO_UTF8(*UserID));
		char* userid = _strdup(useridstring.c_str());

		string passwordstring(TCHAR_TO_UTF8(*Password));
		char* password = _strdup(passwordstring.c_str());

		string Eparamstring;

		for (auto eParam : ExtraParams)
		{
			char* eparamkey(TCHAR_TO_UTF8(*eParam.Key));
			char* eparamvalue(TCHAR_TO_UTF8(*eParam.Value));

			string EparamKey(eparamkey);
			string EparamValue(eparamvalue);

			Eparamstring += EparamKey + "," + EparamValue + ";";
		}

		char* eparamstring = _strdup(Eparamstring.c_str());

		const char* errormessage = "";
		bool connectionpropertystate = m_SetConnectionPropertiesFromDll(title, dbname, userid, password, eparamstring, errormessage);

		ErrorMessage = FString(UTF8_TO_TCHAR(errormessage));
		return connectionpropertystate;

	}

	return false;
}


bool DLLManager::UpdateDataFromQuery(FString Query, FString& ErrorMessage)
{
	if (ImportMethodUpdateDataFromQuery())
	{
		string query(TCHAR_TO_UTF8(*Query));
		char* q = _strdup(query.c_str());

		const char* errormessage = "";
		bool UpdateStatus = m_UpdateDataFromQueryFromDll(q, errormessage);
		ErrorMessage = FString(UTF8_TO_TCHAR(errormessage));

		return UpdateStatus;

	}

	return false;
}

bool DLLManager::SelectDataFromQuery(FString Query, FString& ErrorMessage, TArray<FMySQLDataTable>& ResultByColumn, TArray<FMySQLDataRow>& ResultByRow)
{
	if (ImportMethodSelectDataFromQuery())
	{
		string query(TCHAR_TO_UTF8(*Query));
		char* q = _strdup(query.c_str());

		const char* errormessage = "";


		FString UserDirectory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
		string udstring(TCHAR_TO_UTF8(*UserDirectory));
		char* udir = _strdup(udstring.c_str());

		bool SelectStatus = m_SelectDataFromQueryFromDll(q, udir, errormessage);
		ErrorMessage = FString(UTF8_TO_TCHAR(errormessage));

		if (SelectStatus)
		{

			FString ColumnNamesPath = FPaths::Combine(UserDirectory, TEXT("SelectColumnNames.txt"));
			if (FPaths::FileExists(ColumnNamesPath))
			{
				FString ColumnNames = "";
				FFileHelper::LoadFileToString(ColumnNames, *ColumnNamesPath, FFileHelper::EHashOptions::EnableVerify);

				FString* LeftS = &ColumnNames;
				FString* RightS = nullptr;

				TArray<FString> ColumnNamesArray = GetSplitStringArray(ColumnNames, "<&&columnbreak>");
				for (auto& ColumnName : ColumnNamesArray)
				{

					FMySQLDataTable NewDataTable;
					NewDataTable.ColumnName = ColumnName;
					ResultByColumn.Add(NewDataTable);

				}

			}

			FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*ColumnNamesPath);

			FString ColumnDataPath = FPaths::Combine(UserDirectory, TEXT("SelectColumnData.txt"));
			if (FPaths::FileExists(ColumnDataPath))
			{
				FString ColumnData = "";
				FFileHelper::LoadFileToString(ColumnData, *ColumnDataPath, FFileHelper::EHashOptions::EnableVerify);

				TArray<FString> RowDataArray = GetSplitStringArray(ColumnData, "<&&rowbreak>");

				for (auto& rowdata : RowDataArray)
				{
					FMySQLDataRow Row;
					TArray<FString> ColumnDataArray = GetSplitStringArray(rowdata, "<&&columnbreak>");
					for (auto& cdata : ColumnDataArray)
					{
					    int32 CIndex = ColumnDataArray.IndexOfByKey(cdata);
						if (ResultByColumn.Num() > CIndex)
						{
							ResultByColumn[CIndex].ColumnData.Add(cdata);
						}
						Row.RowData.Add(cdata);

					}


					ResultByRow.Add(Row);

				}


			}

			FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*ColumnDataPath);


		}
		
		return SelectStatus;

	}

	return false;
}

#endif
