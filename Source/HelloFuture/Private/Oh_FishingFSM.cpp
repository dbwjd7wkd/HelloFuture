// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_FishingFSM.h"
#include "HelloFutureCharacter.h"
#include "Math/UnrealMathUtility.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include "FishingAnimInstance.h"
#include <Animation/AnimNode_StateMachine.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values for this component's properties
UOh_FishingFSM::UOh_FishingFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	
}


// Called when the game starts
void UOh_FishingFSM::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AHelloFutureCharacter>(GetOwner());
	anim = Cast<UFishingAnimInstance>(me->GetMesh()->GetAnimInstance());
	m_state = EFishingState::Idle;
	anim->state = m_state;
	
}


// Called every frame
void UOh_FishingFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (m_state)
	{
	case EFishingState::Idle:
		IdleState();
		break;
	case EFishingState::fishingStart:
		StartState();
		break;
	case EFishingState::fishingLoop:
		LoopState();
		break;
	case EFishingState::fishingNibble:
		NibbleState();
		break;
	case EFishingState::fishingBite:
		BiteState();
		break;
	case EFishingState::fishingEnd:
		EndState();
		break;
	}


}

void UOh_FishingFSM::IdleState()
{
	UE_LOG(LogTemp, Warning, TEXT("Idle"));
	anim->state = m_state;
	/*if(me->FishingStart == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("111"));
			m_state = EFishingState::fishingStart;
	}

	else if (me->FishingStart == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("333"));
	}*/
	
}

void UOh_FishingFSM::StartState()
{
	UE_LOG(LogTemp, Warning, TEXT("Start"));
	
	anim->state = m_state;
	NibbleMiss = false;
	BiteMiss = false;

	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > fishingStartTime)
	{
		m_state = EFishingState::fishingLoop;
		currentTime = 0;
		anim->state = m_state;
	}

}

void UOh_FishingFSM::LoopState()
{
	//anim->isfishingLoop = true;
	UE_LOG(LogTemp, Warning, TEXT("Roop"));
	anim->state = m_state;
	currentTime += GetWorld()->DeltaTimeSeconds;

	int32 RandomTime = FMath::RandRange(1, 4);
	
	if (RandomTime == 1 && currentTime> LoopTime)
	{
		m_state = EFishingState::fishingNibble;
		currentTime = 0;
	}
	else if (RandomTime == 2 && currentTime > LoopTime2)
	{
		m_state = EFishingState::fishingNibble;
		currentTime = 0;
	}
	else if (RandomTime == 3 && currentTime > LoopTime3)
	{
		m_state = EFishingState::fishingNibble;
		currentTime = 0;
	}
	else if (RandomTime == 4 && currentTime > LoopTime4)
	{
		m_state = EFishingState::fishingNibble;
		currentTime = 0;
	}
}

void UOh_FishingFSM::NibbleState()
{
	UE_LOG(LogTemp, Warning, TEXT("Nibble"));
	anim->state = m_state;
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > LimitTime)
	{
		NibbleMiss = true;
		m_state = EFishingState::Idle;
		currentTime = 0;
		me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}

}

void UOh_FishingFSM::BiteState()
{
	UE_LOG(LogTemp, Warning, TEXT("Bite"));
	anim->state = m_state;
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (BiteNumber == 10 && currentTime < BiteTime)
	{
		UE_LOG(LogTemp, Warning, TEXT("BiteFinish"));
		m_state = EFishingState::fishingEnd;
		BiteNumber = 0;
		currentTime = 0;
	}
	else if( currentTime > BiteTime)
	{
		BiteMiss = true;
		m_state = EFishingState::Idle;
		BiteNumber = 0;
		currentTime = 0;
		me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		
	}


}

void UOh_FishingFSM::EndState()
{
	UE_LOG(LogTemp, Warning, TEXT("End"));
	anim->state = m_state;
	//currentTime += GetWorld()->DeltaTimeSeconds;

	/*if(currentTime > EndTime)
	{
	m_state = EFishingState::Idle;
	}*/
	
}

