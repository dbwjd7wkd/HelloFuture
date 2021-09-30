// Fill out your copyright notice in the Description page of Project Settings.


#include "OH_InteractiveDialogue2.h"
#include "OH_PlayerController.h"
#include "OH_QuestUI.h"

void AOH_InteractiveDialogue2::Interact()
{

	if (bIsInteracting)
	{
		return;
	}

	if ((currentPlayerController != nullptr) && (Dialogue != nullptr))
	{

		bIsInteracting = true;

		// �÷��̾� ��ǲ ���
		currentPlayerController->SetCinematicMode(true, true, true);


		// ���̾�α� ��������
		currentPlayerController->GetUI()->InitializeDialogue(Dialogue);


		// ���̾�α� �Ϸ�
		currentPlayerController->GetUI()->OnDialogueCompleted.AddDynamic(this, &AOH_InteractiveDialogue2::OnDialogueCompleted);
	}
}

void AOH_InteractiveDialogue2::OnDialogueCompleted()
{
	if (currentPlayerController != nullptr)
	{
		currentPlayerController->SetCinematicMode(false, true, true);

		currentPlayerController->GetUI()->OnDialogueCompleted.RemoveDynamic(this, &AOH_InteractiveDialogue2::OnDialogueCompleted);


	}

	bIsInteracting = false;

}
