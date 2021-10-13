// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Minsu_ShakeTree.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMinsu_ShakeTree : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELLOFUTURE_API IMinsu_ShakeTree
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Farm)
		void ShakeTree();
};
