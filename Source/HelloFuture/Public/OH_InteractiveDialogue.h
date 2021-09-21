// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OH_InteractiveBase.h"
#include "OH_InteractiveDialogue.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API AOH_InteractiveDialogue : public AOH_InteractiveBase
{
	GENERATED_BODY()
	
public:

	void Interact() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	class UDataTable* Dialogue;

	UFUNCTION()
	void OnDialogueCompleted();

	bool bIsInteracting = false;


};
