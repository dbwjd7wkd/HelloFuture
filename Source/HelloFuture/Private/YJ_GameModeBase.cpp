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
	// 1. ����ִ� ���ǥ ������ ��ȣ�� ���� ���Ӹ���� ���� order�� �´��� Ȯ��
	//player = Cast<AHelloFutureCharacter>(GetOwner());

	if (player)
	{
		for (auto item : player->Inventory->Items)
		{
			// 2. ���� ��� �������� �ִٸ�
			if (Cast<UYJ_WaitingTicketItem>(item))
			{
				// ���� ��� ������ ��ȣ�� ��ȣ�� ������ ���ٸ� true ��ȯ (��ȭ����)
				if (item->ItemWaitingNumber == order) return true;
				// �װ� �ƴ϶�� false ��ȯ
				else return false;
			}
		}

		// 3. ���� ��� �������� ���ٸ� false ��ȯ
		return false;
	}

	return true;
}
