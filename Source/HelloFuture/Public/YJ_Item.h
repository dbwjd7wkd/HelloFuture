// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YJ_Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class HELLOFUTURE_API UYJ_Item : public UObject
{
	GENERATED_BODY()
	
public:

	UYJ_Item();

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
	class UWorld* World;

	/**The text for using the item. (Equip, Eat, etc)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText Category;

	///**The mesh to display for this items pickup*/
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	//	class UStaticMesh* PickupMesh;

	/**The thumbnail for this item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbnail;

	/**The display name for this item in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;

	/**An optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	/**The price for this item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 Price;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 MinPrice;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		int32 MaxPrice;

	/**The count for this item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		int32 Count;

	/**The InventoryIndex for this item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		int32 InventoryIndex;

	/**The ItemIndex for this item*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		int32 ItemIndex;

	/**The inventory that owns this item*/
	UPROPERTY()
		class UYJ_InventoryComponent* OwningInventory;

	virtual void Use(class AHelloFutureCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
		void OnUse(class AHelloFutureCharacter* Character);

};
