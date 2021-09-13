// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_InventoryComponent.h"
#include "YJ_Item.h"
#include "Kismet/GameplayStatics.h"
#include "YJ_GameModeBase.h"

// Sets default values for this component's properties
UYJ_InventoryComponent::UYJ_InventoryComponent()
{
	Capacity = 8;
	accountBalance = 0;
	cash = 0;
}

// Called when the game starts
void UYJ_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
	
}

bool UYJ_InventoryComponent::AddItem(UYJ_Item* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	UWorld* const World = GetWorld();
	AYJ_GameModeBase* GameMode;
	if (World) {
		GameMode = Cast<AYJ_GameModeBase>(UGameplayStatics::GetGameMode(World));
		Item->ItemWaitingNumber = GameMode->waitingNumber;
	}

	Item->OwningInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);
	
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::RemoveItem(UYJ_Item* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}

	return false;
}