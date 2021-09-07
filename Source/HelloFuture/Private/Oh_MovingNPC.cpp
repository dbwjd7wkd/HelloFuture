// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_MovingNPC.h"
#include <AIController.h>
#include <NavigationSystem.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>

// Sets default values
AOh_MovingNPC::AOh_MovingNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOh_MovingNPC::BeginPlay()
{
	Super::BeginPlay();
	

	ai = Cast<AAIController>(GetController());

	ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	m_state = ENPCState::Idle;
	

}

// Called every frame
void AOh_MovingNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (m_state)
	{
	case ENPCState::Idle:
		IdleState();
		break;
	case ENPCState::Walk:
		WalkState();
		break;
	}


	currnetTime2 += GetWorld()->DeltaTimeSeconds;

	if (currnetTime2 > createTime)
	{

		int32 Precent = FMath::RandRange(1, 100);

		if (Precent <= Rate1)
		{
			UE_LOG(LogTemp, Warning, TEXT("시장에 물건이 정말 많은걸?"));
			//FString chat = FString::Printf(TEXT("Hi"));
		}
		else if (Rate1 <= Precent && Precent <= Rate2)
		{
			UE_LOG(LogTemp, Warning, TEXT("오 저건 맛있어 보이네"));
			//FString chat2 = FString::Printf(TEXT("2"));
		}
		else if (Rate2 <= Precent && Precent <= Rate3)
		{
			UE_LOG(LogTemp, Warning, TEXT("피곤해 죽겠네.."));
			//FString chat3 = FString::Printf(TEXT("3"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("오쌍은 멋쟁이야"));
			//FString chat4 = FString::Printf(TEXT("4"));
		}

		currnetTime2 = 0;
		return;
	}
}

// Called to bind functionality to input
void AOh_MovingNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOh_MovingNPC::IdleState()
{
	currnetTime += GetWorld()->DeltaTimeSeconds;

	if (currnetTime > idleDelayTime)
	{
		m_state = ENPCState::Walk;
		
		currnetTime = 0;

		randomPos = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), 1500);
	}

	
}

void AOh_MovingNPC::WalkState()
{
	GetCharacterMovement()->MaxWalkSpeed = 300;


	

	//EPathFollowingRequestResult::Type r = ai->MoveToLocation(randomPos);

	// 랜덤 위치로 가자 
	if (ai->MoveToLocation(randomPos) == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		// 이동 가능한 랜덤위치 가져오기
		//randomPos = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), 1500);

		m_state = ENPCState::Idle;

		currnetTime = 0;
	}
}

//bool AOh_MovingNPC::GetTargetLocation(const AActor* targetActor, float radius, FVector& dest)
//{
//	FNavLocation loc;
//	bool result = ns->GetRandomReachablePointInRadius(targetActor->GetActorLocation(), radius, loc);
//	dest = loc.Location;
//
//	return result;
//}

