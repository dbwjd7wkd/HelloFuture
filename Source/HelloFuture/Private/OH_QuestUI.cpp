// Fill out your copyright notice in the Description page of Project Settings.


#include "OH_QuestUI.h"
#include "Components/TextBlock.h"

void UOH_QuestUI::SetMessage(const FString& Text)
{
	if (PlayerDialogTextBlock == nullptr) return;
	
	PlayerDialogTextBlock->SetText(FText::FromString(Text));
}

void UOH_QuestUI::SetCharacterName(const FString& Text)
{
	if (CharacterNameText == nullptr) return;

	CharacterNameText->SetText(FText::FromString(Text));
}
