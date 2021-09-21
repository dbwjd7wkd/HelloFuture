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


	/*virtual void InitializeComponent() override;*/
	
private:


	virtual void BeginPlay() override;

	/*UFUNCTION(BlueprintCallable, Category = "Input")
	void LockInput;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ULockInput;*/


public:
AOH_PlayerController();

class AHelloFutureCharacter* me;

UPROPERTY(BlueprintReadWrite, Category = "Player UI")
class UOH_QuestUI* oh_QuestUI;

TSubclassOf<class UUserWidget> oh_QuestUIclass;

FORCEINLINE UOH_QuestUI* GetUI() {return oh_QuestUI; };

void SetupInputComponent();


public:

UFUNCTION(BlueprintCallable, Category = "Input")
void Interact2();

UFUNCTION(BlueprintCallable, Category = "Input")
void OnKeyUp();

UFUNCTION(BlueprintCallable, Category = "Input")
void OnKeyDown();

UFUNCTION()
void OnintroDialogueCompleted();

//UPROPERTY(BlueprintAssignable)
//FOnActionPress OnActionPressed;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	class UDataTable* IntroDialogue;


	



};
