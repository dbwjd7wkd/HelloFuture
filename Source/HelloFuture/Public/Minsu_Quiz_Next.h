// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minsu_Quiz.h" 
#include "COmponents/SpotLightComponent.h"
#include "Minsu_Quiz_Next.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API AMinsu_Quiz_Next : public AMinsu_Quiz
{
	GENERATED_BODY()
	
public:
	virtual void Interact() override;

	UPROPERTY()
		bool State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Intensity;

	UPROPERTY(EditAnywhere)
		USpotLightComponent* Light;

	AMinsu_Quiz_Next();
};
