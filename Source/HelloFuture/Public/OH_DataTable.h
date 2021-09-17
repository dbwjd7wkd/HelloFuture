 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "OH_DataTable.generated.h"


USTRUCT(BlueprintType)
struct FMessageOptions
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText OptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AnswerIndex;
};

USTRUCT(BlueprintType)
struct FDialogueNPC :public FTableRowBase
{

	GENERATED_BODY()

public:
	/*FDialogue()
	{
		CharacterName = FText::FromString("Name");
		Message = FText::FromString("Hello");
		MessageOptions = FText::FromString("Your Character is...");
	}*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FText> Message;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMessageOptions> MessageOptions;

};


UCLASS()
class HELLOFUTURE_API UOH_DataTable : public UDataTable
{
	GENERATED_BODY()
	
};
