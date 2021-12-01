// Copyright 2021, Athian Games. All Rights Reserved. 


#include "MySQLAsyncTasks.h"
#include "MySQLDBConnectionActor.h"
#include "MySQLBPLibrary.h"


OpenConnectionTask::OpenConnectionTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString server, FString dBName, FString userID, FString password, TMap<FString, FString> extraParams)
{
	Server = server;
	DBName = dBName;
	UserID = userID;
	Password = password;
	ExtraParams = extraParams;
	CurrentDBConnectionActor = dbConnectionActor;
	MySQLDBConnector = dbConnector;
}

OpenConnectionTask::~OpenConnectionTask()
{

}


void OpenConnectionTask::DoWork()
{

	if (MySQLDBConnector)
	{
		FString ErrorMessage;
		bool ConnectionStatus = MySQLDBConnector->CreateNewConnection(Server, DBName, UserID, Password, ExtraParams, ErrorMessage);
		AMySQLDBConnectionActor* dbConnectionActor = CurrentDBConnectionActor;

		AsyncTask(ENamedThreads::GameThread, [dbConnectionActor, ConnectionStatus, ErrorMessage]()
		{
			if (dbConnectionActor && dbConnectionActor->IsValidLowLevel())
			{
				dbConnectionActor->bIsConnectionBusy = false;
				dbConnectionActor->OnConnectionStateChanged(ConnectionStatus, dbConnectionActor->CurrentConnectionID, ErrorMessage);
				dbConnectionActor->CurrentConnectionID = dbConnectionActor->CurrentConnectionID + 1;

			}
			
		});

	}
	
}



UpdateQueryAsyncTask::UpdateQueryAsyncTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString query)
{
	Query = query;
	CurrentDBConnectionActor = dbConnectionActor;
	MySQLDBConnector = dbConnector;

}

UpdateQueryAsyncTask::~UpdateQueryAsyncTask()
{

}

void UpdateQueryAsyncTask::DoWork()
{
	if (MySQLDBConnector)
	{
		bool UpdateQueryStatus;
		FString ErrorMessage;
		//UMySQLBPLibrary::UpdateDataFromQuery(Query, UpdateQueryStatus, ErrorMessage);
		MySQLDBConnector->UpdateDataFromQuery(Query, UpdateQueryStatus, ErrorMessage);
		AMySQLDBConnectionActor* dbConnectionActor = CurrentDBConnectionActor;
		AsyncTask(ENamedThreads::GameThread, [dbConnectionActor, UpdateQueryStatus, ErrorMessage]()
		{
			if (dbConnectionActor && dbConnectionActor->IsValidLowLevel())
			{

				dbConnectionActor->bIsConnectionBusy = false;
				dbConnectionActor->OnQueryUpdateStatusChanged(UpdateQueryStatus, ErrorMessage);
			}
		});
	}
}


SelectQueryAsyncTask::SelectQueryAsyncTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString query)
{
	Query = query;
	CurrentDBConnectionActor = dbConnectionActor;
	MySQLDBConnector = dbConnector;

}

SelectQueryAsyncTask::~SelectQueryAsyncTask()
{

}

void SelectQueryAsyncTask::DoWork()
{
	if (MySQLDBConnector)
	{

		bool UpdateQueryStatus;
		FString ErrorMessage;
		TArray<FMySQLDataTable> ResultByColumn;
		TArray<FMySQLDataRow> ResultByRow;
		//UMySQLBPLibrary::SelectDataFromQuery(Query, UpdateQueryStatus, ErrorMessage, ResultByColumn, ResultByRow);
		MySQLDBConnector->SelectDataFromQuery(Query, UpdateQueryStatus, ErrorMessage, ResultByColumn, ResultByRow);
		AMySQLDBConnectionActor* dbConnectionActor = CurrentDBConnectionActor;
		AsyncTask(ENamedThreads::GameThread, [dbConnectionActor, UpdateQueryStatus, ErrorMessage, ResultByColumn, ResultByRow]()
		{
			if (dbConnectionActor && dbConnectionActor->IsValidLowLevel())
			{
				dbConnectionActor->bIsConnectionBusy = false;
				dbConnectionActor->OnQuerySelectStatusChanged(UpdateQueryStatus, ErrorMessage, ResultByColumn, ResultByRow);
			}
		});
	}
}


UpdateImageAsyncTask::UpdateImageAsyncTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString query, FString updateParameter, int parameterID, FString imagePath)
{
	Query = query;
	UpdateParameter = updateParameter;
	ParameterID = parameterID;
	ImagePath = imagePath;
	CurrentDBConnectionActor = dbConnectionActor;
	MySQLDBConnector = dbConnector;

}

UpdateImageAsyncTask::~UpdateImageAsyncTask()
{

}

void UpdateImageAsyncTask::DoWork()
{
	bool UpdateQueryStatus;
	FString ErrorMessage;
	UMySQLBPLibrary::UpdateImageFromPath(Query, UpdateParameter, ParameterID, ImagePath, UpdateQueryStatus, ErrorMessage);

	AMySQLDBConnectionActor* dbConnectionActor = CurrentDBConnectionActor;
	AsyncTask(ENamedThreads::GameThread, [dbConnectionActor, UpdateQueryStatus, ErrorMessage]()
		{
			if (dbConnectionActor && dbConnectionActor->IsValidLowLevel())
			{

				dbConnectionActor->bIsConnectionBusy = false;
				dbConnectionActor->OnImageUpdateStatusChanged(UpdateQueryStatus, ErrorMessage);
			}

		});
}


SelectImageAsyncTask::SelectImageAsyncTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString query, FString selectParameter)
{
	Query = query;
	SelectParameter = selectParameter;
	CurrentDBConnectionActor = dbConnectionActor;
	MySQLDBConnector = dbConnector;

}

SelectImageAsyncTask::~SelectImageAsyncTask()
{

}

void SelectImageAsyncTask::DoWork()
{
	bool SelectQueryStatus;
	FString ErrorMessage;
	UTexture2D* SelectedTexture = UMySQLBPLibrary::SelectImageFromQuery(Query, SelectParameter, SelectQueryStatus, ErrorMessage);

	AMySQLDBConnectionActor* dbConnectionActor = CurrentDBConnectionActor;
	AsyncTask(ENamedThreads::GameThread, [dbConnectionActor, SelectQueryStatus, ErrorMessage, SelectedTexture]()
		{
			if (dbConnectionActor && dbConnectionActor->IsValidLowLevel())
			{

				dbConnectionActor->bIsConnectionBusy = false;
				dbConnectionActor->OnImageSelectStatusChanged(SelectQueryStatus, ErrorMessage, SelectedTexture);
			}
		});
}





