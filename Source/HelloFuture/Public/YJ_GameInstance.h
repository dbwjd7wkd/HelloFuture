// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "YJ_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UYJ_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	UYJ_GameInstance();
	
public:

	// �÷��� �� ��� �����۵� ��ü ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
		TArray<class UYJ_Item*> AllItems;

};
