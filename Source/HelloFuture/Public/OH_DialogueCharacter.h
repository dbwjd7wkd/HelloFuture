// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "OH_DialogueCharacter.generated.h"


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
class HELLOFUTURE_API AOH_DialogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOH_DialogueCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
