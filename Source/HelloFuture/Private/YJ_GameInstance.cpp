// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_GameInstance.h"
#include "YJ_Item.h"

UYJ_GameInstance::UYJ_GameInstance()
{
    //UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT("Good"));
    
	// cornseed 아이템 만들기
    //item_CornSeed = NewObject<UYJ_Item>(this, UYJ_Item::StaticClass(), FName("CornSeed"));
    //if (item_CornSeed != nullptr)
    //{
    //    ConstructorHelpers::FObjectFinder<UTexture2D> CornSeed_Image(TEXT("Texture2D'/Game/YJ/Blueprints/Inventory/InventoryImage/CornSeed.CornSeed'"));
    //    if (CornSeed_Image.Succeeded())
    //    {
    //        item_CornSeed->Thumbnail = CornSeed_Image.Object;
    //    }
    //    item_CornSeed->ItemDisplayName = FText::FromString(TEXT("CornSeed"));
    //    item_CornSeed->ItemDescription = FText::FromString(TEXT("CornSeed"));
    //    item_CornSeed->Price = 300;
    //    AllItems.Add(item_CornSeed);
    //}

}
