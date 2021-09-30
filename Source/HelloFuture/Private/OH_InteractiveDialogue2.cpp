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

		// 플레이어 인풋 잠금
		currentPlayerController->SetCinematicMode(true, true, true);


		// 다이얼로그 가져오기
		currentPlayerController->GetUI()->InitializeDialogue(Dialogue);


		// 다이얼로그 완료
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
