// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OH_InteractiveBase.h"
#include "OH_InteractiveDialogue3.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API AOH_InteractiveDialogue3 : public AOH_InteractiveBase
{
	GENERATED_BODY()
	
public:

	void Interact() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	bool bIsInteracting = false;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
		class UDataTable* Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
		class UDataTable* Dialogue2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
		class UDataTable* Dialogue3;

	UFUNCTION(BlueprintCallable, Category = Event)
		void OnDialogueCompleted();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
		bool interactQuest = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
		bool interactQuestclear = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
		bool camera = false;


};
