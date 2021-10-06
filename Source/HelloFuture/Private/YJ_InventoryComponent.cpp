// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_InventoryComponent.h"
#include "YJ_Item.h"
#include "Kismet/GameplayStatics.h"
#include "YJ_GameModeBase.h"
#include "YJ_WaitingTicketItem.h"
#include "YJ_GameModeBase.h"
#include "YJ_GameInstance.h"

// Sets default values for this component's properties
UYJ_InventoryComponent::UYJ_InventoryComponent()
{

	accountBalance = 10000;
	cash = 5000;

	columnLength = 7;
	rowLength = 3;
	Capacity = columnLength * rowLength; // 20

	//Items.SetNum(Capacity);
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
	// 인벤토리 창이 다 차거나 들어오는 Item 이 유효하지 않으면 아래 내용 실행하지 않음.
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	// Item이 은행 대기표일 때, Items에 대기표가 있으면 아래 내용 실행하지 않음.
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
	state = "add";
	Items.Add(Item);
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

// 게임인스턴스의 AllItems 배열에서 Item번째 YJ_Item 을 가져와서 add
bool UYJ_InventoryComponent::AddItem2(EItemEnum Item)
{
	// 인벤토리 창이 다 차면 아래 내용 실행하지 않음.
	if (ItemCnt >= Capacity)
	{
		return false;
	}

	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UGameInstance* gameInst = world->GetGameInstance();
	if (!gameInst) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(gameInst);
	if (!gameInstance) return false;

	// 아이템 가져오기
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];

	// Item이 은행 대기표일 때, Items에 대기표가 있으면 아래 내용 실행하지 않음.
	UYJ_WaitingTicketItem* waitingTicketItem = Cast<UYJ_WaitingTicketItem>(item);
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

	// 아이템 추가하기
	state = "add";
	// 수정하기!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if(item->Count <= 0)
	{
		item->OwningInventory = this;
		item->World = GetWorld();
		item->ItemIndex = idx;
		item->InventoryIndex = ItemCnt;
		item->Count = 1;
		//Items[ItemCnt] = item;
		Items.Add(item);
		ItemCnt++;
	}
	else
	{
		//Items[item->InventoryIndex]->Count++;
		item->Count++;
	}
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::RemoveItem(UYJ_Item* Item)
{
	// 인벤토리 창이 비거나 들어오는 Item 이 유효하지 않으면 아래 내용 실행하지 않음.
	if (Items.Num() <= 0 || !Item)
	{
		return false;
	}

	Item->OwningInventory = nullptr;
	Item->World = nullptr;
	Items[ItemCnt] = nullptr;
	//Items.RemoveSingle(Item);
	state = "remove";
	OnInventoryUpdated.Broadcast();
	return true;
}

// 게임인스턴스의 AllItems 배열에서 Item번째 YJ_Item 을 가져와서 remove
bool UYJ_InventoryComponent::RemoveItem2(EItemEnum Item)
{
	// sellingitem2 UI의 RemoveItem2에서 false가 반환이 됨 수정!!!!!!!!!!!!!!!!!!!!
	// 인벤토리 창이 비면 아래 내용 실행하지 않음.
	if (ItemCnt <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
		return false;
	}


	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UGameInstance* gameInst = world->GetGameInstance();
	if (!gameInst) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(gameInst);
	if (!gameInstance) return false;

	// 아이템 가져오기
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];

	// 아이템 지우기

	state = "remove";

	if (item->Count <= 1)
	{
		item->OwningInventory = nullptr;
		item->World = nullptr;
		item->ItemIndex = idx;
		item->InventoryIndex = -1;
		item->Count = 0;
		//Items[ItemCnt] = nullptr;
		Items.RemoveSingle(item);
		//Items.SetNum(Capacity);
		ItemCnt--;
		UE_LOG(LogTemp, Warning, TEXT("Remove Item"));
		UE_LOG(LogTemp, Warning, TEXT("%d"), Items.Num());
	}
	else
	{
		//Items[item->InventoryIndex]->Count--;
		item->Count--;
		UE_LOG(LogTemp, Warning, TEXT("Minus item count"));
	}
	OnInventoryUpdated.Broadcast();

	return true;
}

int32 UYJ_InventoryComponent::GetItemIndex(UYJ_Item* Item)
{
	// 인벤토리에 Item이 있으면 인덱스 반환
	int idx = -1;
	for (auto inven_item : Items)
	{
		idx++;
		if (inven_item->ItemDisplayName.ToString() == Item->ItemDisplayName.ToString())
		{
			return idx;
		}
	}
	// 없으면 -1	반환
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
