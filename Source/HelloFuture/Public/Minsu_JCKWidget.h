// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HelloFutureCharacter.h"
#include "YJ_InventoryComponent.h"
#include "Minsu_JCKWidget.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UMinsu_JCKWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JCKSettings)
		class AHelloFutureCharacter* helloFuturePlayer;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JCKSettings)
// 		class UYJ_InventoryComponent* YJInventory;

// 	UFUNCTION(BlueprintImplementableEvent, Category = JCKSettings)
// 		void TextCash();
// 
// 	UFUNCTION(BlueprintImplementableEvent, Category = JCKSettings)
// 		void TextAccount();
// 
// 	UFUNCTION(BlueprintImplementableEvent, Category = JCKSettings)
// 		void TextName();
};
