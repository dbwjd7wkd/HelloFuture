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

	accountBalance = 10000;
	cash = 5000;

	columnLength = 7;
	rowLength = 3;
	Capacity = columnLength * rowLength; // 20


}

// Called when the game starts
void UYJ_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//for (auto& Item : DefaultItems)
	//{
	//	AddItem(Item);
	//}
	
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

	//int idx = GetItemIndex(Item);
	//// ���� �κ��丮�� Item�� �ִٸ� ���� ����
	//if (idx >= 0)
	//{
	//	ItemsCount[idx]++;
	//}
	//// �װ� �ƴ϶�� �κ��丮�� Item �߰�
	//else
	//{
	//	Items.Add(Item);
	//}

	Items.Add(Item);
	state = "add";
	
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::RemoveItem(UYJ_Item* Item)
{
	// �κ��丮 â�� �� ���ų� ������ Item �� ��ȿ���� ������ �Ʒ� ���� �������� ����.
	if (Items.Num() <= 0 || !Item)
	{
		return false;
	}

	Item->OwningInventory = nullptr;
	Item->World = nullptr;

	//int idx = GetItemIndex(Item);
	//// ���� �κ��丮�� Item�� �ְ� ������ 2�� �̻��̶�� ���� ����
	//if (ItemsCount[idx] >= 2)
	//{
	//	ItemsCount[idx]--;
	//}
	//// �װ� �ƴϰ� ������ 1�� ���϶�� �κ��丮�� Item �߰�
	//else if(ItemsCount[idx] <= 1)
	//{
	//	ItemsCount[idx] = 0;
	//	Items.RemoveSingle(Item);
	//}

	Items.RemoveSingle(Item);
	state = "remove";
	OnInventoryUpdated.Broadcast();
	return true;

}

int32 UYJ_InventoryComponent::GetItemIndex(UYJ_Item* Item)
{
	// �κ��丮�� Item�� ������ �ε��� ��ȯ
	int idx = -1;
	for (auto inven_item : Items)
	{
		idx++;
		if (inven_item->ItemDisplayName.ToString() == Item->ItemDisplayName.ToString())
		{
			return idx;
		}
	}
	// ������ -1	��ȯ
	return -1;
}

bool UYJ_InventoryComponent::MinusCash(int32 minusPrice)
{
	if (cash - minusPrice >= 0)
	{
		cash = cash - minusPrice;
		return true;
	}
	else return false;
}

bool UYJ_InventoryComponent::PlusCash(int32 plusPrice)
{
	cash = cash + plusPrice;
	return true;
}

bool UYJ_InventoryComponent::MinusAccountBalance(int32 minusPrice)
{
	if (accountBalance - minusPrice >= 0)
	{
		accountBalance = accountBalance - minusPrice;
		return true;
	}
	else return false;
}

bool UYJ_InventoryComponent::PlusAccountBalance(int32 plusPrice)
{
	accountBalance = accountBalance + plusPrice;
	return true;
}
