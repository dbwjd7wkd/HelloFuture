// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YJ_Item.h"
#include "YJ_FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UYJ_FoodItem : public UYJ_Item
{
	GENERATED_BODY()

public:
	/**The weight of the item*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
		float HealthToHeal;
	
protected:
	virtual void Use(class AHelloFutureCharacter* Character) override;
};
