// Fill out your copyright notice in the Description page of Project Settings.


#include "GH_LastClickedTMap.h"

// Sets default values
AGH_LastClickedTMap::AGH_LastClickedTMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LastClicked.Add("Head");
	LastClicked.Add("HairStyle");
	LastClicked.Add("Nose");
	LastClicked.Add("UpperClothes");
	LastClicked.Add("UnderClothes");
	LastClicked.Add("WholeClothes");
	LastClicked.Add("Glasses");
	LastClicked.Add("Hat");
	LastClicked.Add("Bag");
	LastClicked.Add("Watch");

}

// Called when the game starts or when spawned
void AGH_LastClickedTMap::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AGH_LastClickedTMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AGH_LastClickedTMap::GetLastClickedItem(FString key)
{
// key가 FString이 아니면???
	// 들어온 key가 유효한지 확인 -> TMap에 존재하는지 확인, FString이 
	FString value;
	FString* isKey = LastClicked.Find(key);
	if (isKey != nullptr)
	{
	// 유효하면 값을 돌려줌
		value = LastClicked[key];
	}
	// 유효하지 않으면 "Null"을 돌려줌
	value = "";

	return value;
}

void AGH_LastClickedTMap::SetLastClickedItem(FString key, FString value)
{
	// 자동으로 오버로딩됨
	LastClicked.Add(key, value);
}

void AGH_LastClickedTMap::InitLastClickedItem()
{
	LastClicked.Add("Head");
	LastClicked.Add("HairStyle");
	LastClicked.Add("Nose");
	LastClicked.Add("UpperClothes");
	LastClicked.Add("UnderClothes");
	LastClicked.Add("WholeClothes");
	LastClicked.Add("Glasses");
	LastClicked.Add("Hat");
	LastClicked.Add("Bag");
	LastClicked.Add("Watch");
}

