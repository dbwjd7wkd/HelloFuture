// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <OH_DataTable.cpp>
#include <HelloFuture/Public/OH_DataTable.h>
#include "OH_QuestUI.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueCompletedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNextDialogueStartDelegate);
/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UOH_QuestUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "UI Message Settings")
	float DelayBetweenLetters = 0.2f;

	UPROPERTY(EditAnywhere, Category = "UI Message Settings")
	class USoundBase* SoundCueMessage;

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerDialogTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CharacterNameText;

	/*UPROPERTY(meta = (BindWidget))
		class UTextBlock* OptionText_0;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* OptionText_1;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* OptionText_2;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* OptionText_3;*/

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
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnResetOptions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnHighLightOption(int32 option);

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnSetOption(int32 Option, const FText& OptionText);




public:
	
	void SetMessage(const FString& Text);

	void SetCharacterName(const FString& Text);

	void AnimateMessage(const FString& Text);

	void Interact();


	void InitializeDialogue(class UDataTable* DialogueTable);
		 
	void OnSelectUpOption();

	void OnSelectDownOption();








private:
	FTimerHandle TimerHandle;

	UFUNCTION()
	void OnTimerCompleted();

	UFUNCTION()
		void OnAnimationTimerCompleted();

	bool bAnimating = false;

	bool bTextCompleted = false;

	FString InitialMessage;

	FString OutputMessage;

	int32 iLetter;


private:
	
	int32 CurrentState = 0;

	int32 SelectectedOption;

	
	TArray<FDialogueNPC*> dialogue;

	int32 MessageIndex;

	int32 RowIndex;


public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FDialogueCompletedDelegate OnDialogueCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FNextDialogueStartDelegate OnNextDialogueStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* curDialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool finish = false;
	
};
