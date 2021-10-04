// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OH_InteractiveBase.h"
#include "OH_InteractiveInitialDialogue.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API AOH_InteractiveInitialDialogue : public AOH_InteractiveBase
{
	GENERATED_BODY()
	

//private:
//	UFUNCTION()
//		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);
//
//	UFUNCTION()
//		virtual void EndOverlap(UPrimitiveComponent* overlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
		class UDataTable* Dialogue;

		/*UFUNCTION(BlueprintCallable, Category = Event)
			void OnDialogueCompleted();*/

	bool bIsInteracting = false;


};
