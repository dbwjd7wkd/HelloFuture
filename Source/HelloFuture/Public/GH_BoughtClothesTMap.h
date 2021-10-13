// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GH_BoughtClothesTMap.generated.h"

UCLASS()
class HELLOFUTURE_API AGH_BoughtClothesTMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGH_BoughtClothesTMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoughtClothes)
		TMap<FString, bool> BoughtClothes;

	UFUNCTION(BlueprintCallable, Category = BoughtClothes)
		bool GetBoughtClothes(FString key);

	UFUNCTION(BlueprintCallable, Category = BoughtClothes)
		void SetBoughtClothes(FString key, bool value);
};
