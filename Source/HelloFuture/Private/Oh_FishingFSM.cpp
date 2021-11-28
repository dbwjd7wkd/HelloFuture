// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_FishingFSM.h"
#include "HelloFutureCharacter.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UOh_FishingFSM::UOh_FishingFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOh_FishingFSM::BeginPlay()
{
	Super::BeginPlay();

	m_state = EFishingState::Idle;
	
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
	case EFishingState::fishingRoop:
		RoopState();
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
	
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > fishingStartTime)
	{
		m_state = EFishingState::fishingRoop;
		currentTime = 0;
	}

}

void UOh_FishingFSM::RoopState()
{
	UE_LOG(LogTemp, Warning, TEXT("Roop"));
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

	/*if (currentTime <= NibbleTime )
	{
		if (me->Fishing())
		{

		}
	}*/

}

void UOh_FishingFSM::BiteState()
{

}

void UOh_FishingFSM::EndState()
{

}

