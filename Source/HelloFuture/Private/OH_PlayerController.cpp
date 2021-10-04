// Fill out your copyright notice in the Description page of Project Settings.


#include "OH_PlayerController.h"
#include "OH_QuestUI.h"
#include "UObject/ConstructorHelpers.h"
#include "HelloFutureCharacter.h"
#include "HelloFutureGameMode.h"
#include "Apple.h"



AOH_PlayerController::AOH_PlayerController()
{
	
static ConstructorHelpers::FClassFinder<UUserWidget> oh_QuestUIBPclass(TEXT("/Game/Oh/BP/WBP_OH_QuestUI"));


	if (oh_QuestUIBPclass.Class != nullptr)
	{
		oh_QuestUIclass = oh_QuestUIBPclass.Class;
	}


}




void AOH_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* const pawn = GetPawn();

	if (pawn != nullptr)
	{
		me = Cast<AHelloFutureCharacter>(pawn);
	}
	
	
	

	if (oh_QuestUIclass != nullptr)
	{
		oh_QuestUI = CreateWidget<UOH_QuestUI>(this, oh_QuestUIclass);
		
	}

	if (oh_QuestUI != nullptr)
	{
		oh_QuestUI->AddToViewport();


		//oh_QuestUI->AnimateMessage("Blue Robot", "This is");
		//oh_QuestUI->SetMessage("HELLO WORLD!");
		//oh_QuestUI->SetCharacterName("OH_SSang");
		//oh_QuestUI->OnAinmationsShowMessageUI();
		/*if(IntroDialogue  != nullptr)
		{
			if(isPlaying == true)
			{
			SetCinematicMode(true,true,true);

			oh_QuestUI->InitializeDialogue(IntroDialogue);

			oh_QuestUI->OnDialogueCompleted.AddDynamic(this, &AOH_PlayerController::OnintroDialogueCompleted);
			}

		}*/

	}

}


void AOH_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IntroDialogue != nullptr)
	{
		if (isPlaying == true)
		{
			SetCinematicMode(true, true, true);

			oh_QuestUI->InitializeDialogue(IntroDialogue);

			oh_QuestUI->OnDialogueCompleted.AddDynamic(this, &AOH_PlayerController::OnintroDialogueCompleted);
		}

	}

}



void AOH_PlayerController::OnintroDialogueCompleted()
{
	if (oh_QuestUI != nullptr)
	{
		oh_QuestUI->OnDialogueCompleted.RemoveDynamic(this, &AOH_PlayerController::OnintroDialogueCompleted);
	}
	SetCinematicMode(false, true, true);

	

}

void AOH_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ohInteract",IE_Pressed, this, &AOH_PlayerController::Interact);
	
	InputComponent->BindAction("KeyUp",IE_Pressed, this, &AOH_PlayerController::OnKeyUp).bConsumeInput =false;

	InputComponent->BindAction("KeyDown",IE_Pressed, this, &AOH_PlayerController::OnKeyDown).bConsumeInput =false;




}

void AOH_PlayerController::Interact()
{
	//OnActionPressed.Broadcast();
	if ((me != nullptr) && (me->GetInteractive() != nullptr))
	{
		me->GetInteractive()->Interact();
	}


	if (oh_QuestUI != nullptr)
	{
		oh_QuestUI-> Interact();
	}


	
}

void AOH_PlayerController::OnKeyUp()
{

	if (oh_QuestUI != nullptr)
	{
		oh_QuestUI->OnSelectUpOption();
	}
}

void AOH_PlayerController::OnKeyDown()
{

	if (oh_QuestUI != nullptr)
	{
		oh_QuestUI->OnSelectDownOption();
	}
}


