// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Engine/SkeletalMesh.h"
#include "Materials/MaterialInterface.h"
#include "YJ_InventoryComponent.h"
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
UENUM(BlueprintType)
enum class EClosetBoughtCategory : uint8
{
    Category1 UMETA(DisplayName = "None"),
    Category2 UMETA(DisplayName = "Head"),
    Category3 UMETA(DisplayName = "HairStyle"),
    Category4 UMETA(DisplayName = "Nose"),
    Category5 UMETA(DisplayName = "UpperClothes"),
    Category6 UMETA(DisplayName = "UnderClothes"),
    Category7 UMETA(DisplayName = "WholeClothes"),
    Category8 UMETA(DisplayName = "Glasses"),
    Category9 UMETA(DisplayName = "Hat"),
    Category10 UMETA(DisplayName = "Bag"),
    Category11 UMETA(DisplayName = "Watch"),
    Category12 UMETA(DisplayName = "HatHair"),
    Category13 UMETA(DisplayName = "Hair_Acc_R"),
    Category14 UMETA(DisplayName = "Hair_Acc_BB"),
};


USTRUCT(Atomic, BlueprintType)
struct FcloseBoughtMStruct
{
    GENERATED_BODY()
public:
    // 구매한 옷 순서대로 in 옷장(Material array)-내부 배열

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        USkeletalMesh* closetBoughtMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<UMaterialInterface*> closetBoughtMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
       EClosetBoughtCategory closetBoughtCategory;
};

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

    //// 구매한 옷 순서대로 in 옷장(array)
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
    //    TArray<FString> closetBought;

    /*
    // 구매한 옷 순서대로 in 옷장(Mesh array)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<USkeletalMesh*> closetBoughtMesh;

    // 구매한 옷 순서대로 in 옷장(Material array)-외부 배열
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<FcloseBoughtMStruct> closetBoughtMaterialStruct;
    */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<FcloseBoughtMStruct> closetBoughts;

    // 통장이자
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
        FBankBookInterestStruct BankBook;

    // 대출
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
        FLoanStruct Loan;

    // 세금
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
        FTaxStruct Tax;

	// 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
        int32 worldTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		FDateTime worldTime_Structure;
};
