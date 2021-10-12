// Fill out your copyright notice in the Description page of Project Settings.

#include "YJ_SaveGame.h"
#include "HelloFutureCharacter.h"
#include "YJ_Item.h"

UYJ_SaveGame::UYJ_SaveGame()
{
	SaveSlotName = TEXT("MySaveSlot");
	UserIndex = 0;

	for (int i = 0; i < 40; i++) // 아이템 추가되면 갯수 늘려야 함
	{
		inventoryIdx.Add(-1);
		inventoryCnt.Add(0);
	}
	//itemIdx.Init(20, -1); // 총 아이템 20개에 대해 인덱스 -1 부여 // 오류남

 //   Items.Empty();
	//accountBalance = 10000;
	//cash = 5000;

	//columnLength = 10;
	//rowLength = 2;
	//Capacity = columnLength * rowLength; // 20
}
