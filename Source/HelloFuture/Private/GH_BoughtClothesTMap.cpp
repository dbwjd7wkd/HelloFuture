// Fill out your copyright notice in the Description page of Project Settings.


#include "GH_BoughtClothesTMap.h"

// Sets default values
AGH_BoughtClothesTMap::AGH_BoughtClothesTMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoughtClothes.Add("ShopClothes1", false);
	BoughtClothes.Add("ShopClothes2", false);
	BoughtClothes.Add("ShopClothes3", false);
	BoughtClothes.Add("ShopClothes4", false);
	BoughtClothes.Add("ShopClothes5", false);

}

// Called when the game starts or when spawned
void AGH_BoughtClothesTMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGH_BoughtClothesTMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGH_BoughtClothesTMap::GetBoughtClothes(FString key)
{
	bool value;
	bool* isKey = BoughtClothes.Find(key);
	if (isKey != nullptr)
	{
		// ��ȿ�ϸ� ���� ������
		value = BoughtClothes[key];
	}
	return value;
}

void AGH_BoughtClothesTMap::SetBoughtClothes(FString key, bool value)
{
	// �ڵ����� �����ε���
	BoughtClothes.Add(key, value);
}

