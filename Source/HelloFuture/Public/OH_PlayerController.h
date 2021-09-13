// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OH_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API AOH_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

public:
AOH_PlayerController();

class AMinsu_Character* me;

UPROPERTY(BlueprintReadWrite, Category = "Player UI")
class UOH_QuestUI* oh_QuestUI;

TSubclassOf<class UUserWidget> oh_QuestUIclass;

FORCEINLINE UOH_QuestUI* GetUI() {return oh_QuestUI; };

void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

public:

UFUNCTION(BlueprintCallable, Category = "Input")
void Interact2();



};
