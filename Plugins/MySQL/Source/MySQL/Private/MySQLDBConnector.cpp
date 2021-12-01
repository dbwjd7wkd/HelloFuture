// Copyright 2021, Athian Games. All Rights Reserved. 


#include "MySQLDBConnector.h"

UMySQLDBConnector::UMySQLDBConnector()
{
	bIsConnectionBusy = false;


}

bool UMySQLDBConnector::CreateNewConnection(FString Server, FString DBName, FString UserID, FString Password, TMap<FString, FString> ExtraParams,
	FString& ErrorMessage)
{
	bool isConnectionSet = false;

	if (!bIsConnectionBusy)
	{
		bIsConnectionBusy = true;
		if (DLLManager::LoadDLL("MySQLLibrary.dll"))
		{
			isConnectionSet = DLLManager::SetConnectionProperties(Server, DBName, UserID, Password, ExtraParams, ErrorMessage);

		}
		else
		{
			ErrorMessage = "Dll Error. Ensure that you have the correct dlls in your project Binaries. You can get the files from the example project. Download the example project from the Marketplace Description Page.";
		}

		bIsConnectionBusy = false;

	}
	
	return isConnectionSet;

}

void  UMySQLDBConnector::CloseConnection()
{
	if (DLLManager::LoadDLL("MySQLLibrary.dll"))
	{
		DLLManager::CloseConnection();
		DLLManager::UnLoadDLL();
	}

}

void UMySQLDBConnector::UpdateDataFromQuery(FString Query, bool& IsSuccessful, FString& ErrorMessage)
{
	if (!bIsConnectionBusy)
	{
		bIsConnectionBusy = true;
		if (DLLManager::LoadDLL("MySQLLibrary.dll"))
		{
			IsSuccessful = DLLManager::UpdateDataFromQuery(Query, ErrorMessage);
			DLLManager::UnLoadDLL();
		}

		bIsConnectionBusy = false;
	}


}


void UMySQLDBConnector::SelectDataFromQuery(FString Query, bool& IsSuccessful, FString& ErrorMessage,
	TArray<FMySQLDataTable>& ResultByColumn, TArray<FMySQLDataRow>& ResultByRow)
{

	if (!bIsConnectionBusy)
	{
		bIsConnectionBusy = true;

		if (DLLManager::LoadDLL("MySQLLibrary.dll"))
		{
			IsSuccessful = DLLManager::SelectDataFromQuery(Query, ErrorMessage, ResultByColumn, ResultByRow);
			DLLManager::UnLoadDLL();
		}

		bIsConnectionBusy = false;

	}



}

