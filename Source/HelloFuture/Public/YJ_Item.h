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
		FText UseActionText;

	/**The mesh to display for this items pickup*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UStaticMesh* PickupMesh;

	/**The thumbnail for this item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbnail;

	/**The display name for this item in the inventory*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;

	/**An optional description for the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	/**The weight of the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
		int32 ItemWaitingNumber;

	/**The inventory that owns this item*/
	UPROPERTY()
		class UYJ_InventoryComponent* OwningInventory;

	virtual void Use(class AHelloFutureCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
		void OnUse(class AHelloFutureCharacter* Character);

};
