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
	
protected:
	UPROPERTY(EditAnywhere, Category = "UI Message Settings")
	float DelayBetweenLetters = 0.3f;

	UPROPERTY(EditAnywhere, Category = "UI Message Settings")
	class USoundBase* SoundCueMessage;

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
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnResetOptions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	void OnHighLightOption(int32 option);

	//UFUNCTION(BlueprintImplementableEvent, Category = "Animation Events")
	//void OnSetOption(int32, const FText& OptionText);




public:
	
	void SetMessage(const FString& Text);

	void SetCharacterName(const FString& Text);

	void AnimateMessage(const FString& Name, const FString& Text);

	void Interact2();


private:
	FTimerHandle TimerHandle;

	UFUNCTION()
	void OnTimerCompleted();

	bool bAnimating = false;

	bool bTextCompleted = false;

	FString InitialMessage;

	FString OutputMessage;

	int32 iLetter;
};
