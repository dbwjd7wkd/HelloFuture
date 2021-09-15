// Fill out your copyright notice in the Description page of Project Settings.


#include "OH_QuestUI.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>

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

void UOH_QuestUI::AnimateMessage(const FString& Name, const FString& Text)
{
	bTextCompleted = false;

	bAnimating = false;

	CharacterNameText->SetText(FText::FromString(Name));

	if(Text.Len()==0) return;

	InitialMessage = Text;
	
	iLetter = 0;

	OnAinmationsShowMessageUI();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOH_QuestUI::OnTimerCompleted, 0.5f, false);
}



void UOH_QuestUI::OnTimerCompleted()
{
	OutputMessage.AppendChar(InitialMessage[iLetter]);
	PlayerDialogTextBlock->SetText(FText::FromString(OutputMessage));

	if (SoundCueMessage != nullptr)
	{
		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, SoundCueMessage, 0.5f);
	}

	if ((iLetter + 1) < InitialMessage.Len())
	{
		iLetter = iLetter + 1;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOH_QuestUI::OnTimerCompleted, DelayBetweenLetters, false);

	}
	else
	{
		bTextCompleted = true;
		bAnimating = false;
	}
}

void UOH_QuestUI::Interact2()
{
	if (!bAnimating)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		bAnimating = false;

		PlayerDialogTextBlock->SetText(FText::FromString(InitialMessage));

		bTextCompleted = true;
	}
	else if (bTextCompleted)
	{
		bTextCompleted = false;

		OnAinmationsHideMessageUI();
	}
}

void UOH_QuestUI::InitializeDialogue(class UOH_DataTable* DialogueTable)
{

}

void UOH_QuestUI::OnSelectUpOption()
{

}

void UOH_QuestUI::OnSelectDownOption()
{

}
