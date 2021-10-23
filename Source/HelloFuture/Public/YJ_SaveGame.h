// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Engine/SkeletalMesh.h"
#include "Materials/MaterialInterface.h"
#include "YJ_SaveGame.generated.h"

/**
 * 
 */
//UENUM(BlueprintType)
//enum class EItem : uint8
//{
//    E_Warrior = 0   UMETA(DisplayName = "Warrior"),	//! DisplayName�� �𸮾� ������, �������Ʈ���� ǥ�õǴ� �̸��Դϴ�.
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
    // ������ �� ������� in ����(Material array)-���� �迭

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

    // �÷��̾� ����
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
        FText PlayerName;

    UPROPERTY(VisibleAnywhere, Category = "Basic")
        float time;

    // �κ��丮
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

    // �κ��丮 ������ ����
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<int32> inventoryIdx; // �κ��丮�� �� ������ �ε���

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<int32> inventoryCnt; // �κ��丮�� �� ������ ����

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
        int32 ItemCnt;

    // ���� ����
    //UPROPERTY(VisibleAnywhere, Category = "Inventory")
    //    TArray<class UYJ_Item*> Items;


    // ������ ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoughtClothes")
        TMap<FString, bool> BoughtClothes;

    // ����Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
    UActorComponent* saveQuest;

    //// ������ �� ������� in ����(array)
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
    //    TArray<FString> closetBought;

    /*
    // ������ �� ������� in ����(Mesh array)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<USkeletalMesh*> closetBoughtMesh;

    // ������ �� ������� in ����(Material array)-�ܺ� �迭
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<FcloseBoughtMStruct> closetBoughtMaterialStruct;
    */

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
        TArray<FcloseBoughtMStruct> closetBoughts;
};
