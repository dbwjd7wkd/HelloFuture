// Fill out your copyright notice in the Description page of Project Settings.


#include "OH_PlayerController.h"
#include "OH_QuestUI.h"
#include "UObject/ConstructorHelpers.h"
#include "Minsu_Character.h"
#include "HelloFutureCharacter.h"


AOH_PlayerController::AOH_PlayerController()
{
static ConstructorHelpers::FClassFinder<UUserWidget> oh_QuestUIBPclass(TEXT("/Game/Oh/BP/WBP_OH_QuestUI"));

	if (oh_QuestUIBPclass.Class != nullptr)
	{
		oh_QuestUIclass = oh_QuestUIBPclass.Class;
	}


}

void AOH_PlayerController::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact",IE_Pressed, this, &AOH_PlayerController::Interact2);

	InputComponent->BindAction("KeyUp",IE_Pressed, this, &AOH_PlayerController::OnKeyUp).bConsumeInput =false;

	InputComponent->BindAction("KeyDown",IE_Pressed, this, &AOH_PlayerController::OnKeyDown).bConsumeInput =false;



}

void AOH_PlayerController::Interact2()
{
	if (oh_QuestUI != nullptr)
	{
		oh_QuestUI-> Interact2();
	}
}

void AOH_PlayerController::OnKeyUp()
{

	if (oh_QuestUI != nullptr)
	{
		//oh_QuestUI->OnSelectUpOption();
	}
}

void AOH_PlayerController::OnKeyDown()
{

	if (oh_QuestUI != nullptr)
	{
		//oh_QuestUI->OnSelectDownOption();
	}
}

void AOH_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	
		me = Cast<AHelloFutureCharacter>(GetOwner());
	

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
		if(IntroDialogue  != nullptr)
		{
			SetCinematicMode(true,true,true);
			oh_QuestUI->InitializeDialogue(IntroDialogue);
		}

	}

}
