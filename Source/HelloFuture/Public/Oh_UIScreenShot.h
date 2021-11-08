// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealClient.h"
#include "Oh_UIScreenShot.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UOh_UIScreenShot : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintCallable, Category = UI_Screenshot)
		static void TakeScreenshotOfUI(FString name) {
			FScreenshotRequest::RequestScreenshot(name, true, false);
		}
	
};
