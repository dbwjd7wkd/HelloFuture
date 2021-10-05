// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_Item.h"

UYJ_Item::UYJ_Item()
{
	ItemDisplayName = FText::FromString("Item");
	Category = FText::FromString("Use");

	Count = 0;
	InventoryIndex = -1;
	ItemIndex = -1;
}

void UYJ_Item::Use(class AHelloFutureCharacter* Character)
{

}
