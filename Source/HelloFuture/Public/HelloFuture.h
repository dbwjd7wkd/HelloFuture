// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"

DECLARE_LOG_CATEGORY_EXTERN(HelloFuture, Log, All);

#define APPINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define CALLINFO() UE_LOG(HelloFuture, Warning, TEXT("%s"), *APPINFO)
#define PRINTLOG(fmt, ...) UE_LOG(HelloFuture, Warning, TEXT("%s %s"), *APPINFO, *FString::Printf(fmt, ##__VA_ARGS__) )