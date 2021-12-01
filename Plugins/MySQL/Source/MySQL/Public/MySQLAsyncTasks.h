// Copyright 2021, Athian Games. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Engine/DataTable.h"
#include "Async/Async.h"

#include "MySQLDBConnector.h"

/**
 * 
 */

class AMySQLDBConnectionActor;

class MYSQL_API OpenConnectionTask : public FNonAbandonableTask
{

private:

	FString Server;
	FString DBName;
	FString UserID;
	FString Password;
	FString ExtraParam;
	AMySQLDBConnectionActor* CurrentDBConnectionActor;
	TMap<FString, FString> ExtraParams;

	UMySQLDBConnector* MySQLDBConnector;

public:


	OpenConnectionTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString server, FString dBName, FString userID, FString password, TMap<FString, FString> extraParams);

	virtual ~OpenConnectionTask();
	virtual void DoWork();
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(OpenConnectionTask, STATGROUP_ThreadPoolAsyncTasks);
	}

};


class MYSQL_API UpdateQueryAsyncTask : public FNonAbandonableTask
{

private:

	FString Query;
	AMySQLDBConnectionActor* CurrentDBConnectionActor;
	UMySQLDBConnector* MySQLDBConnector;

public:


	UpdateQueryAsyncTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString query);

	virtual ~UpdateQueryAsyncTask();
	virtual void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UpdateQueryAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

};


class MYSQL_API SelectQueryAsyncTask : public FNonAbandonableTask
{

private:

	FString Query;
	AMySQLDBConnectionActor* CurrentDBConnectionActor;
	UMySQLDBConnector* MySQLDBConnector;

public:


	SelectQueryAsyncTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString query);

	virtual ~SelectQueryAsyncTask();
	virtual void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(SelectQueryAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

};


class MYSQL_API UpdateImageAsyncTask : public FNonAbandonableTask
{

private:

	FString Query;
	AMySQLDBConnectionActor* CurrentDBConnectionActor;
	FString UpdateParameter;
	int ParameterID;
	FString ImagePath;
	UMySQLDBConnector* MySQLDBConnector;

public:


	UpdateImageAsyncTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString query, FString updateParameter, int parameterID, FString imagePath);

	virtual ~UpdateImageAsyncTask();
	virtual void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UpdateImageAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

};


class MYSQL_API SelectImageAsyncTask : public FNonAbandonableTask
{

private:

	FString Query;
	AMySQLDBConnectionActor* CurrentDBConnectionActor;
	FString SelectParameter;
	UMySQLDBConnector* MySQLDBConnector;

public:


	SelectImageAsyncTask(AMySQLDBConnectionActor* dbConnectionActor, UMySQLDBConnector* dbConnector, FString query, FString selectParameter);

	virtual ~SelectImageAsyncTask();
	virtual void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(SelectImageAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

};




