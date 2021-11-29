// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Oh_FishingFSM.h"
#include "FishingAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UFishingAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	public:

		UPROPERTY(EditAnywhere, Category = FSM, BlueprintReadOnly)
		EFishingState state;

		UPROPERTY(VisibleAnywhere, Category = "FSM", BlueprintReadOnly)
		bool isfishingStart = false;

		UPROPERTY(VisibleAnywhere, Category = "FSM", BlueprintReadOnly)
		bool isfishingLoop = false;

};
