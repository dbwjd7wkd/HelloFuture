// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "YJ_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API AYJ_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// ����ȣ
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Numbering System")
		int32 waitingNumber = 0;

public:
	UFUNCTION(BlueprintCallable)
		void AddWaitingNumber();
	UFUNCTION(BlueprintCallable)
		void MinusWaitingNumber();
	UFUNCTION(BlueprintCallable)
		bool CheckMyOrder(class AHelloFutureCharacter* player);
};
