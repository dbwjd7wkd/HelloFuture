// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "YJ_InventoryComponent.h"
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
	UFUNCTION(BlueprintCallable)
	class UYJ_Item* GetItemAsEnum(EItemEnum itemEnum);

	UFUNCTION(BlueprintCallable)
	FString GetMyIpAddress();
	
public:
	// 플레이 시 모든 아이템들 객체 들어가있음
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
		TArray<class UYJ_Item*> AllItems;

	// custoM에서 구매한 옷을 배치할 위치 백터 어레이 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetSpawnLocation")
		TArray<FVector> closetSpawnLocation;

	// 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int32 worldTime = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		FDateTime worldTime_Structure;
};
