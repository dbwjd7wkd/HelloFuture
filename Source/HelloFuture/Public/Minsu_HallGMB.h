// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Minsu_HallGMB.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API AMinsu_HallGMB : public AGameModeBase
{
	GENERATED_BODY()
		virtual void BeginPlay() override;


//protected:
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WebBrowser", Meta = (BlueprintProtected = "true"))
//		TSubclassOf<class UUserWidget> WebBrowserWidgetClass;
//
//	UPROPERTY()
//		class UUserWidget* CurrentWidget;

};
