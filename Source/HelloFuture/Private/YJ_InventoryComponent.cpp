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

	accountBalance = 0;
	cash = 10000;

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
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
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
			if (!GameMode) return false;
			waitingTicketItem->ItemWaitingNumber = GameMode->waitingNumber + 1;
		}
	}

	// 아이템 추가하기
	state = "add";
	
	if(item->Count <= 0)
	{
		item->OwningInventory = this;
		item->World = GetWorld();
		item->ItemIndex = idx;
		item->InventoryIndex = ItemCnt;
		item->Count = 1;
		Items.Add(item);
		ItemCnt++;
	}
	else
	{
		item->Count++;
	}
	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::AddItemByNumber(EItemEnum Item, int32 num)
{
	// 인벤토리 창이 다 차면 아래 내용 실행하지 않음.
	if (ItemCnt >= Capacity)
	{
		return false;
	}

	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
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
			if (!GameMode) return false;
			waitingTicketItem->ItemWaitingNumber = GameMode->waitingNumber + 1;
		}
	}

	// 아이템 추가하기
	state = "add";

	if (item->Count <= 0)
	{
		item->OwningInventory = this;
		item->World = GetWorld();
		item->ItemIndex = idx;
		item->InventoryIndex = ItemCnt;
		item->Count += num;
		Items.Add(item);
		ItemCnt++;
	}
	else
	{
		item->Count += num;
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
	// 인벤토리 창이 비면 아래 내용 실행하지 않음.
	if (ItemCnt <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
		return false;
	}

	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
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
		Items.RemoveSingle(item);
		ItemCnt--;
		UE_LOG(LogTemp, Warning, TEXT("Remove Item"));
		UE_LOG(LogTemp, Warning, TEXT("%d"), Items.Num());
	}
	else
	{
		item->Count--;
		UE_LOG(LogTemp, Warning, TEXT("Minus item count"));
	}

	// Update UI
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UYJ_InventoryComponent::RemoveItemByNumber(EItemEnum Item, int32 num)
{
	// 인벤토리 창이 비면 아래 내용 실행하지 않음.
	if (ItemCnt <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
		return false;
	}

	// 게임인스턴스 가져오기
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	// 아이템 가져오기
	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];

	if (item->Count < num) return false;

	// 아이템 지우기
	state = "remove";

	if (item->Count - num <= 0)
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
		item->Count -= num;
		UE_LOG(LogTemp, Warning, TEXT("Minus item count"));
	}
	OnInventoryUpdated.Broadcast();

	return true;
}

UYJ_Item* UYJ_InventoryComponent::EnumIndexToItem(EItemEnum Item)
{
	UWorld* world = GetWorld();
	if (!world) return false;
	UYJ_GameInstance* gameInstance = Cast<UYJ_GameInstance>(world->GetGameInstance());
	if (!gameInstance) return false;

	int32 idx = (int32)Item;
	UYJ_Item* item = gameInstance->AllItems[idx];
	if (item)
	{
		for (auto itm : Items)
		{
			if (itm == item)
			{
				return itm;
			}
		}
	}
	return nullptr;
}

bool UYJ_InventoryComponent::CheckHaveItemAsYJ_Item(class UYJ_Item* Item)
{
	if (Item->InventoryIndex >= 0) return true;
	else return false;
}

bool UYJ_InventoryComponent::CheckHaveItemAsEnum(EItemEnum Item)
{
	UYJ_Item* item = UYJ_InventoryComponent::EnumIndexToItem(Item);

	for (auto itm : Items)
	{
		if (itm == item)
		{
			return true;
		}
	}

	return false;
	//if (!item) return false;

	//if (item->Count > 0) return true;
	//else return false;
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

bool UYJ_InventoryComponent::Update_Tax()
{
	Tax_RemainingDate++;

	if (Tax_RemainingDate % 7 == 0)
	{
		Tax_Content = FMath::RandRange(0, 4);

		switch (Tax_Content)
		{
		case 0:
			Tax_Percent = 3;
			break;
		case 1:
			Tax_Percent = 5;
			break;
		case 2:
			Tax_Percent = 8;
			break;
		case 3: 
			Tax_Percent = 10;
			break;
		case 4:
			Tax_Percent = 15;
			break;
		default:
			break;
		}

		Tax_Interest = (accountBalance + cash) * Tax_Percent * 0.01;
		onTaxUpdated.Broadcast();
	}

	return true;
}
