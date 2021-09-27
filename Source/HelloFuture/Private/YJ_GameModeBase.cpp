// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_GameModeBase.h"
#include "HelloFutureCharacter.h"
#include "YJ_InventoryComponent.h"
#include "YJ_WaitingTicketItem.h"

void AYJ_GameModeBase::AddWaitingNumber()
{
	waitingNumber++;
}

void AYJ_GameModeBase::MinusWaitingNumber()
{
	waitingNumber--;
}

bool AYJ_GameModeBase::CheckMyOrder(AHelloFutureCharacter* player)
{
	// 1. 들고있는 대기표 아이템 번호가 지금 게임모드의 순서 order와 맞는지 확인
	//player = Cast<AHelloFutureCharacter>(GetOwner());

	if (player)
	{
		for (auto item : player->Inventory->Items)
		{
			// 2. 만약 대기 아이템이 있다면
			UYJ_WaitingTicketItem* waitingTicketItem = Cast<UYJ_WaitingTicketItem>(item);
			if (waitingTicketItem)
			{
				// 만약 대기 아이템 번호가 번호판 순서와 같다면 true 반환 (대화시작)
				if (waitingTicketItem->ItemWaitingNumber == waitingNumber) return true;
				// 순서가 다르다면 false 반환
				else return false;
			}
		}

		// 3. 만약 대기 아이템이 없다면 false 반환
		return false;
	}

	return false;
}
