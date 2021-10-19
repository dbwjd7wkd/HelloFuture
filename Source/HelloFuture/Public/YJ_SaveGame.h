// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "YJ_SaveGame.generated.h"

/**
 * 
 */
//UENUM(BlueprintType)
//enum class EItem : uint8
//{
//    E_Warrior = 0   UMETA(DisplayName = "Warrior"),	//! DisplayName은 언리얼 에디터, 블루프린트에서 표시되는 이름입니다.
//    E_Mage			UMETA(DisplayName = "Mage"),
//    E_Archer		UMETA(DisplayName = "Archer"),
//
//    E_MAX,
//};

UCLASS()
class HELLOFUTURE_API UYJ_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:

    UYJ_SaveGame();

    // save slot
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
        int32 UserIndex;

    // 플레이어 정보
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
        FText PlayerName;

    UPROPERTY(VisibleAnywhere, Category = "Basic")
        float time;

    // 인벤토리
    UPROPERTY(VisibleAnywhere, Category = "Inventory")
        int32 accountBalance;

    UPROPERTY(VisibleAnywhere, Category = "Inventory")
        int32 cash;

    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    int32 columnLength;

    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    int32 rowLength;
    //
    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    int32 Capacity;

    // 인벤토리 아이템 정보
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<int32> inventoryIdx; // 인벤토리의 각 아이템 인덱스

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<int32> inventoryCnt; // 인벤토리의 각 아이템 갯수

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        int32 ItemCnt;

    // 삭제 예정
    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    TArray<class UYJ_Item*> Items;


    // 구매한 옷
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoughtClothes")
        TMap<FString, bool> BoughtClothes;

    // 퀘스트
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
    UActorComponent* saveQuest;

    // 맵의 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PreLevelName")
        FString preLevelName = "MainMap";

};
