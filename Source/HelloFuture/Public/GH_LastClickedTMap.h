// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GH_LastClickedTMap.generated.h"

UCLASS()
class HELLOFUTURE_API AGH_LastClickedTMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGH_LastClickedTMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LastClicked)
		TMap<FString, FString> LastClicked;

	UFUNCTION(BlueprintCallable, Category = LastCliked)
	FString GetLastClickedItem(FString key);

	UFUNCTION(BlueprintCallable, Category = LastCliked)
	void SetLastClickedItem(FString key, FString value);

	UFUNCTION(BlueprintCallable, Category = LastCliked)
	void InitLastClickedItem();
};
