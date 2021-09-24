// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Minsu_QuizUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UMinsu_QuizUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int32 Score;
};
