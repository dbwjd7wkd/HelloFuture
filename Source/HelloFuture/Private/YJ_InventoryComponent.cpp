// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_InventoryComponent.h"
#include "YJ_Item.h"
#include "Kismet/GameplayStatics.h"
#include "YJ_GameModeBase.h"
#include "YJ_WaitingTicketItem.h"
#include "YJ_GameModeBase.h"

// Sets default values for this component's properties
UYJ_InventoryComponent::UYJ_InventoryComponent()
{
	Capacity = 20;
	accountBalance = 10000;
	cash = 5000;
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
	// �κ��丮 â�� �� ���ų� ������ Item �� ��ȿ���� ������ �Ʒ� ���� �������� ����.
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	// Item�� ���� ���ǥ�� ��, Items�� ���ǥ�� ������ �Ʒ� ���� �������� ����.
	UYJ_WaitingTicketItem* waitingTicketItem = Cast<UYJ_WaitingTicketItem>(Item);
	if (waitingTicketItem)
	{
		for (auto yjItem : Items)
		{
			if (Cast<UYJ_WaitingTicketItem>(yjItem) != nullptr)
			{
				return false;
			}
		}

		UWorld* const World = GetWorld();
		AYJ_GameModeBase* GameMode;
		if (World) {
			GameMode = Cast<AYJ_GameModeBase>(UGameplayStatics::GetGameMode(World));
			waitingTicketItem->ItemWaitingNumber = GameMode->waitingNumber + 1;
		}
	}
	
	Item->OwningInventory = this;
	Item->World = GetWorld();

	// �κ��丮�� Item �߰�
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