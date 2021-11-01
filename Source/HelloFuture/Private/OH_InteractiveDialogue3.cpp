// Fill out your copyright notice in the Description page of Project Settings.


#include "OH_InteractiveDialogue3.h"
#include "OH_PlayerController.h"
#include "OH_QuestUI.h"


void AOH_InteractiveDialogue3::Interact()
{
		
	if (bIsInteracting)
	{
		return;
	}

	if ((currentPlayerController != nullptr) && (Dialogue != nullptr))
	{
		
			camera = true;
			bIsInteracting = true;

		
			// �÷��̾� ��ǲ ���
			currentPlayerController->SetCinematicMode(true, true, true);

			if (interactQuestclear == false)
			{
			// ���̾�α� ��������
			currentPlayerController->GetUI()->InitializeDialogue(Dialogue);
			}

			else if (interactQuestclear == true)
			{
			// ���̾�α� ��������
			currentPlayerController->GetUI()->InitializeDialogue(Dialogue2);

			}

			// ���̾�α� �Ϸ�
			currentPlayerController->GetUI()->OnDialogueCompleted.AddDynamic(this, &AOH_InteractiveDialogue3::OnDialogueCompleted);
		

		

		
	}
}

void AOH_InteractiveDialogue3::OnDialogueCompleted()
{
	if (currentPlayerController != nullptr)
	{
		currentPlayerController->SetCinematicMode(false, true, true);

		currentPlayerController->GetUI()->OnDialogueCompleted.RemoveDynamic(this, &AOH_InteractiveDialogue3::OnDialogueCompleted);

			interactQuest = true;

		
	}
	

	bIsInteracting = false;
}
