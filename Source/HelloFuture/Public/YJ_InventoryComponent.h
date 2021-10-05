// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YJ_InventoryComponent.generated.h"

// Blueprints will bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOFUTURE_API UYJ_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UYJ_InventoryComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		bool AddItem(class UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(class UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		int32 GetItemIndex(class UYJ_Item* Item);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<class UYJ_Item*> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<int32> ItemsCount;
	
};
