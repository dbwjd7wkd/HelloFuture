// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyTalkWidget.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UMyTalkWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Text_Talk;

//	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//class UTextBlock* Text_Talk2;
};
