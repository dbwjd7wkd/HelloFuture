// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OH_QuestUI.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UOH_QuestUI : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerDialogTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterNameText;

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnAinmationsShowMessageUI();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnAinmationsHideMessageUI();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnShowMessage();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnHideMessage();
public:
	
	void SetMessage(const FString& Text);

	void SetCharacterName(const FString& Text);
};
