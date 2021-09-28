// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Minsu_Activate.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMinsu_Activate : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLOFUTURE_API IMinsu_Activate
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Farm)
	void Activate();
};
