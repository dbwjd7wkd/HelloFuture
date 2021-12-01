// Copyright 2021, Athian Games. All Rights Reserved. 


#include "MySQLDBConnectionActor.h"

// Sets default values
AMySQLDBConnectionActor::AMySQLDBConnectionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsConnectionBusy = false;

}

// Called when the game starts or when spawned
void AMySQLDBConnectionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySQLDBConnectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySQLDBConnectionActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CloseAllConnections();
	bIsConnectionBusy = false;
	
	if (OpenConnectionTaskPtr && !OpenConnectionTaskPtr->IsIdle())
	{
		OpenConnectionTaskPtr->Cancel();

	}
	if (UpdateQueryAsyncTaskPtr && !UpdateQueryAsyncTaskPtr->IsIdle())
	{
		UpdateQueryAsyncTaskPtr->Cancel();

	}
	if (SelectQueryAsyncTaskPtr && !SelectQueryAsyncTaskPtr->IsIdle())
	{
		SelectQueryAsyncTaskPtr->Cancel();

	}
	if (UpdateImageAsyncTaskPtr && !UpdateImageAsyncTaskPtr->IsIdle())
	{
		UpdateImageAsyncTaskPtr->Cancel();

	}
	if (SelectImageAsyncTaskPtr && !SelectImageAsyncTaskPtr->IsIdle())
	{
		SelectImageAsyncTaskPtr->Cancel();

	}

	Super::EndPlay(EndPlayReason);

	
}

void AMySQLDBConnectionActor::CloseAllConnections()
{
	CurrentConnectionID = 0;
	for (auto& connector : SQLConnectors)
	{
		if (connector.Value)
		{
			connector.Value->CloseConnection();
			connector.Value = NULL;
		}
	}

	SQLConnectors.Empty();
}

UMySQLDBConnector* AMySQLDBConnectionActor::GetConnector(int32 ConnectionID)
{
	UMySQLDBConnector** CurrentConnector = SQLConnectors.Find(ConnectionID);
	if (CurrentConnector && *CurrentConnector)
	{
		return *CurrentConnector;
	}
	else
	{
		return NULL;
	}
}

void AMySQLDBConnectionActor::CreateNewConnection(FString Server, FString DBName, FString UserID, FString Password, TMap<FString, FString> ExtraParams)
{
	if (!bIsConnectionBusy)
	{
		UMySQLDBConnector* NewConnector = NewObject<UMySQLDBConnector>();

		if (!SQLConnectors.Contains(CurrentConnectionID))
		{
			SQLConnectors.Add(CurrentConnectionID);
		}

		SQLConnectors[CurrentConnectionID] = NewConnector;

		OpenConnectionTaskPtr = new FAsyncTask<OpenConnectionTask>(this, NewConnector, Server, DBName, UserID, Password, ExtraParams);
		OpenConnectionTaskPtr->StartBackgroundTask();
		
		bIsConnectionBusy = true;
	}

}


void AMySQLDBConnectionActor::UpdateDataFromQuery(int32 ConnectionID, FString Query)
{
	if (!bIsConnectionBusy)
	{
		
		if (UMySQLDBConnector* CurrentConnector = GetConnector(ConnectionID))
		{
			UpdateQueryAsyncTaskPtr = new FAsyncTask<UpdateQueryAsyncTask>(this, CurrentConnector, Query);
			UpdateQueryAsyncTaskPtr->StartBackgroundTask();
			bIsConnectionBusy = true;

		}
		
	}

}

void AMySQLDBConnectionActor::SelectDataFromQuery(int32 ConnectionID, FString Query)
{
	if (!bIsConnectionBusy)
	{
		if (UMySQLDBConnector* CurrentConnector = GetConnector(ConnectionID))
		{
			SelectQueryAsyncTaskPtr = new FAsyncTask<SelectQueryAsyncTask>(this, CurrentConnector, Query);
			SelectQueryAsyncTaskPtr->StartBackgroundTask();
			bIsConnectionBusy = true;
		}
	}

}

void AMySQLDBConnectionActor::CloseConnection(int32 ConnectionID)
{
	if (UMySQLDBConnector* CurrentConnector = GetConnector(ConnectionID))
	{
		CurrentConnector->CloseConnection();
	}
	bIsConnectionBusy = false;
}


void AMySQLDBConnectionActor::UpdateImageFromPath(int32 ConnectionID, FString Query, FString UpdateParameter, int ParameterID, FString ImagePath)
{
	if (!bIsConnectionBusy)
	{
		if (UMySQLDBConnector* CurrentConnector = GetConnector(ConnectionID))
		{
			UpdateImageAsyncTaskPtr = new FAsyncTask<UpdateImageAsyncTask>(this, CurrentConnector, Query, UpdateParameter, ParameterID, ImagePath);
			UpdateImageAsyncTaskPtr->StartBackgroundTask();
			bIsConnectionBusy = true;
		}
	}

}

bool AMySQLDBConnectionActor::UpdateImageFromTexture(int32 ConnectionID, FString Query, FString UpdateParameter, int ParameterID, UTexture2D* Texture)
{

	if (Texture)
	{
		FString TexturePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("OutputImage.png"));
		TexturePath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*TexturePath);
		bool IsTextureSaved = UMySQLBPLibrary::SaveTextureToPath(Texture, TexturePath);

		if (IsTextureSaved)
		{
			UpdateImageFromPath(ConnectionID, Query, UpdateParameter, ParameterID, TexturePath);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return false;

}


void AMySQLDBConnectionActor::SelectImageFromQuery(int32 ConnectionID, FString Query, FString SelectParameter)
{
	if (!bIsConnectionBusy)
	{
		if (UMySQLDBConnector* CurrentConnector = GetConnector(ConnectionID))
		{
			SelectImageAsyncTaskPtr = new FAsyncTask<SelectImageAsyncTask>(this, CurrentConnector, Query, SelectParameter);
			SelectImageAsyncTaskPtr->StartBackgroundTask();
			bIsConnectionBusy = true;
		}
	}

}