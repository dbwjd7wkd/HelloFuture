// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OH_InteractiveBase.h"
#include "OH_InteractiveDialogue2.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API AOH_InteractiveDialogue2 : public AOH_InteractiveBase
{
	GENERATED_BODY()
	
public:

	void Interact() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
		class UDataTable* Dialogue;

	UFUNCTION(BlueprintCallable, Category = Event)
		void OnDialogueCompleted();

	bool bIsInteracting = false;
};
