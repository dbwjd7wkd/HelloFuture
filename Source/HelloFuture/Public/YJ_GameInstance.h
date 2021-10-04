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

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	//	TArray<class UYJ_Item*> AllItems;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	//	class UYJ_Item* item_CornSeed;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	//	class UYJ_Item* item_Corn;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	//	class UYJ_Item* item_Daikon;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	//	class UYJ_Item* item_Bread;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	//	class UYJ_Item* item_Lemon;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	//	class UYJ_Item* item_Pumpkin;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	//	class UYJ_Item* item_PumpkinSeed;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	//	class UYJ_Item* item_WaterMelon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
		TArray<class UYJ_Item*> AllItems;

	//UFUNCTION(BlueprintCallable)
	//	class UYJ_Item* GetItem(FName itemDisplayName);
};
