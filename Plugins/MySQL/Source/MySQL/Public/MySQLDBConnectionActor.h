// Copyright 2021, Athian Games. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySQLBPLibrary.h"
#include "MySQLAsyncTasks.h"

#include "MySQLDBConnector.h"

#include "MySQLDBConnectionActor.generated.h"


UCLASS()
class MYSQL_API AMySQLDBConnectionActor : public AActor
{
	GENERATED_BODY()
	
private:


	FAsyncTask<OpenConnectionTask>*   OpenConnectionTaskPtr;
	FAsyncTask<UpdateQueryAsyncTask>* UpdateQueryAsyncTaskPtr;
	FAsyncTask<SelectQueryAsyncTask>* SelectQueryAsyncTaskPtr;
	FAsyncTask<UpdateImageAsyncTask>* UpdateImageAsyncTaskPtr;
	FAsyncTask<SelectImageAsyncTask>* SelectImageAsyncTaskPtr;

public:	
	// Sets default values for this actor's properties
	AMySQLDBConnectionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UMySQLDBConnector* GetConnector(int32 ConnectionID);

public:	

	UPROPERTY()
		bool bIsConnectionBusy;


	UPROPERTY()
		TMap<int32, UMySQLDBConnector*> SQLConnectors;

	UPROPERTY()
		int32 CurrentConnectionID;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Creates a New Database Connection
	*
	* @param	Server          SQL Server Name
	* @param	DBName	        Initial Database Name to be connected to
	* @param	UserID	        SQL Server UserID. Not relevant while using Windows Authentication
	* @param	Password    	SQL Server Password. Not relevant while using Windows Authentication
	* @param	ExtraParam   	Additional Connection Parameter to be included
	*/
	UFUNCTION(BlueprintCallable, Category = "MySql Server")
		void CreateNewConnection(FString Server, FString DBName, FString UserID, FString Password, TMap<FString, FString> ExtraParams);

	UFUNCTION(BlueprintCallable, Category = "MySql Server")
		void CloseAllConnections();

	UFUNCTION(BlueprintCallable, Category = "MySql Server")
		void CloseConnection(int32 ConnectionID);

	UFUNCTION(BlueprintImplementableEvent, Category = "MySql Server")
		void OnConnectionStateChanged(bool ConnectionStatus, int32 ConnectionID, const FString& ErrorMessage);

	/**
	* Executes a Query to the database
	*
	* @param	Query           Query which is to be executed to the database
	* @param	SuccessStatus	Returns the status of Query execution , or busy if the connection is already busy
	* @param	ErrorMessage	Returns the exception message thrown if the Query execution fails
	*/
	UFUNCTION(BlueprintCallable, Category = "MySql Server")
		void UpdateDataFromQuery(int32 ConnectionID, FString Query);

	UFUNCTION(BlueprintImplementableEvent, Category = "MySql Server")
		void OnQueryUpdateStatusChanged(bool IsSuccessful, const FString& ErrorMessage);


	/**
	* Selects data from the database
	*
	* @param	Query           Select Query which selects data from the database
   */
	UFUNCTION(BlueprintCallable, Category = "MySql Server")
		void SelectDataFromQuery(int32 ConnectionID, FString Query);

	UFUNCTION(BlueprintImplementableEvent, Category = "MySql Server")
		void OnQuerySelectStatusChanged(bool IsSuccessful, const FString& ErrorMessage, const TArray<FMySQLDataTable>& ResultByColumn, 
			const TArray<FMySQLDataRow>& ResultByRow);


		/**
	* Updates image to the database from the hard drive Asynchronously
	*
	* @param	Query           Update Query which inserts or updates image to the database
	* @param	UpdateParameter Value which has been passed as a parameter for updating the image in the previous input,
								without the @ symbol
	* @param	ParameterID      The Parameter Order ID, so that ImageParameter can be searched afor nd replaced with necessary value
	* @param	Texture        Texture that needs to be converted to image and updated in the SQL Server
	* @param	ErrorMessage	Returns the exception message thrown if the Texture is not successfully read
	*/
	UFUNCTION(BlueprintCallable, Category = "MySql Server")
		bool UpdateImageFromTexture(int32 ConnectionID, FString Query, FString UpdateParameter, int ParameterID, UTexture2D* Texture);

	/**
	* Updates image to the database from the hard drive Asynchronously
	*
	* @param	Query           Update Query which inserts or updates image to the database
	* @param	UpdateParameter Value which has been passed as a parameter for updating the image in the previous input,
								without the @ symbol
	* @param	ParameterID      The Parameter Order ID, so that ImageParameter can be searched afor nd replaced with necessary value
	* @param	ImagePath       Path of the Image that needs to be updated in the SQL Server
	* @param	SuccessStatus	Returns the status of Query execution , or busy if the connection is already busy
	* @param	ErrorMessage	Returns the exception message thrown if the Query execution fails
	*/
	UFUNCTION(BlueprintCallable, Category = "MySql Server")
		void UpdateImageFromPath(int32 ConnectionID, FString Query, FString UpdateParameter, int ParameterID, FString ImagePath);


	UFUNCTION(BlueprintImplementableEvent, Category = "MySql Server")
		void OnImageUpdateStatusChanged(bool IsSuccessful, const FString& ErrorMessage);


	/**
	* Selects image from the database and returns Texture2D format of the selected image
	*
	* @param	Query           Select Query which fetches a single image from the database
	* @param	SelectParameter  The Image Parameter Name
	*/
	UFUNCTION(BlueprintCallable, Category = "MySql Server")
		void SelectImageFromQuery(int32 ConnectionID, FString Query, FString SelectParameter);

	UFUNCTION(BlueprintImplementableEvent, Category = "MySql Server")
		void OnImageSelectStatusChanged(bool IsSuccessful, const FString& ErrorMessage, UTexture2D* SelectedTexture);



};
