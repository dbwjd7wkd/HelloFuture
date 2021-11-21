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


void UOH_QuestUI::InitializeDialogue(class UDataTable* DialogueTable)
{
	curDialog = DialogueTable;
	CurrentState = 0;

	dialogue.Empty();

	CharacterNameText->SetText(FText::FromString(""));
	PlayerDialogTextBlock->SetText(FText::FromString(""));

	OnResetOptions();

	for (auto it : DialogueTable->GetRowMap())
	{
		FDialogueNPC* Row = (FDialogueNPC*)it.Value;

		dialogue.Add(Row);

	}

	RowIndex = 0;
		

	if (dialogue.Num() > 0)
	{
		CurrentState = 0;

		RowIndex = 0;

		CharacterNameText->SetText(FText::FromString(dialogue[RowIndex]->CharacterName.ToString()));

		if (dialogue[RowIndex]->Message.Num() > 0)
		{
			MessageIndex = 0;

			OnAinmationsShowMessageUI();

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOH_QuestUI::OnTimerCompleted, 0.5f, false);
		}
	}

}


void UOH_QuestUI::OnTimerCompleted()
{
	/*OutputMessage.AppendChar(InitialMessage[iLetter]);
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
	}*/

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	AnimateMessage(dialogue[RowIndex]->Message[MessageIndex].ToString());
}


void UOH_QuestUI::AnimateMessage( const FString& Text)
{
	/*bTextCompleted = false;

	bAnimating = false;

	CharacterNameText->SetText(FText::FromString(Name));

	if(Text.Len()==0) return;

	InitialMessage = Text;
	
	iLetter = 0;

	OnAinmationsShowMessageUI();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOH_QuestUI::OnTimerCompleted, 0.5f, false);*/
	

	CurrentState = 1;

	InitialMessage = Text;

	OutputMessage = "";

	iLetter = 0;

	
	PlayerDialogTextBlock->SetText(FText::FromString(""));

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOH_QuestUI::OnAnimationTimerCompleted, DelayBetweenLetters, false);

}





void UOH_QuestUI::OnAnimationTimerCompleted()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	OutputMessage.AppendChar(InitialMessage[iLetter]);

	PlayerDialogTextBlock->SetText(FText::FromString(OutputMessage));

	if (SoundCueMessage != nullptr)
	{
		UAudioComponent* AudioComponenet = UGameplayStatics::SpawnSound2D(this, SoundCueMessage, 0.5f);
	}

	if ((iLetter + 1) < InitialMessage.Len())
	{
		iLetter = iLetter + 1;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOH_QuestUI::OnAnimationTimerCompleted, DelayBetweenLetters, false);
	}
	else
	{
		CurrentState = 2;

		

	}

	

}

void UOH_QuestUI::Interact()
{
	/*if (!bAnimating)
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
	}*/
	
	if (CurrentState == 1)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		PlayerDialogTextBlock->SetText(FText::FromString(InitialMessage));
		
		CurrentState = 2;
	}
	else if (CurrentState == 2)
	{
		OnNextDialogueStart.Broadcast();

		if ((MessageIndex + 1) < dialogue[RowIndex]->Message.Num())
		{ 
			MessageIndex +=1;

			AnimateMessage(dialogue[RowIndex]->Message[MessageIndex].ToString());
			finish = true;
		}

		else
		{
			PlayerDialogTextBlock->SetText(FText::FromString(""));
			CharacterNameText->SetText(FText::FromString(""));

			if (dialogue[RowIndex]->MessageOptions.Num() > 0)
			{
				
				OnResetOptions();

				for (int i = 0; i < dialogue[RowIndex]->MessageOptions.Num(); i++)
				{
					OnSetOption(i, dialogue[RowIndex]->MessageOptions[i].OptionText);
					
				}

				SelectectedOption = 0;

				OnHighLightOption(SelectectedOption);

				CurrentState = 3;

				
			}
			else
			{
				CurrentState = 0;
				OnAinmationsHideMessageUI();

				OnDialogueCompleted.Broadcast();
			}
		}
		
	}
	else if (CurrentState == 3)
	{
		RowIndex =dialogue[RowIndex]->MessageOptions[SelectectedOption].AnswerIndex;
		OnResetOptions();

		if ((RowIndex >= 0) && (RowIndex < dialogue.Num()))
		{
			PlayerDialogTextBlock->SetText(FText::FromString(""));
			

			MessageIndex = 0;
			AnimateMessage(dialogue[RowIndex]->Message[MessageIndex].ToString());
			CharacterNameText->SetText(FText::FromString(dialogue[RowIndex]->CharacterName.ToString()));
		}
		else
		{
			CurrentState = 0;
			OnAinmationsHideMessageUI();

			OnDialogueCompleted.Broadcast();
		}
	}
}



void UOH_QuestUI::OnSelectUpOption()
{
	if(CurrentState != 3) return;

	if ((SelectectedOption - 1) >= 0)
	{
		SelectectedOption -= 1;
		OnHighLightOption(SelectectedOption);
	}
}

void UOH_QuestUI::OnSelectDownOption()
{
	if (CurrentState != 3) return;

	if ((SelectectedOption + 1) < dialogue[RowIndex]->MessageOptions.Num())
	{
		SelectectedOption += 1;
		OnHighLightOption(SelectectedOption);
	}




}
