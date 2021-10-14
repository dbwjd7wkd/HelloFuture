// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YJ_InventoryComponent.generated.h"

// Blueprints will bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UENUM(BlueprintType)
enum class EItemEnum : uint8
{
	Apple = 0,
	ClothingHelmet, // UMETA(DisplayName = "Option B")
	ClothingVest,
	CornItem,
	CornSeed,
	Radish,
	Bread,
	Lemon,
	Pumpkin,
	PumpkinSeed,
	WaterMelon,
	Wheat,
	WheatSeed = 12,
	RadishSeed,
	WaitingTicket,
	Fertilizer,
	Fertilizer2,
	MagicPowder,
	Tonic
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOFUTURE_API UYJ_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UYJ_InventoryComponent();

	virtual void BeginPlay() override;
	// 아이템 관련 함수
	UFUNCTION(BlueprintCallable)
		bool AddItem(class UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool AddItem2(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(class UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem2(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		class UYJ_Item* EnumIndexToItem(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		bool CheckHaveItemAsYJ_Item(class UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool CheckHaveItemAsEnum(EItemEnum Item);

	// 돈 관련 함수
	UFUNCTION(BlueprintCallable)
		bool MinusCash(int32 minusPrice);
	UFUNCTION(BlueprintCallable)
		bool PlusCash(int32 plusPrice);
	UFUNCTION(BlueprintCallable)
		bool MinusAccountBalance(int32 minusPrice);
	UFUNCTION(BlueprintCallable)
		bool PlusAccountBalance(int32 plusPrice);

public:
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UYJ_Item*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated	OnInventoryUpdated;

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	int32 accountBalance;

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	int32 cash;

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	FName state; // add, remove

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	int32 columnLength;
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	int32 rowLength;

	// 인벤토리 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<class UYJ_Item*> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int32 ItemCnt;

	//// SaveGame에 넣을 인벤토리 아이템 정보
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	//	TArray<int32> inventoryCnt; // 인벤토리의 각 아이템 갯수

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	//	TArray<int32> inventoryIdx; // 인벤토리의 각 아이템 인덱스
};
