// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_MovingNPC2.h"
#include <AIController.h>
#include <NavigationSystem.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include "HelloFutureCharacter.h"
#include "OH_InteractiveDialogue3.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/EngineTypes.h>


// Sets default values
AOh_MovingNPC2::AOh_MovingNPC2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOh_MovingNPC2::BeginPlay()
{
	Super::BeginPlay();
	
	ai = Cast<AAIController>(GetController());

	ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	m_state2 = ENPCState2::Idle;


}

// Called every frame
void AOh_MovingNPC2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	switch (m_state2)
	{
	case ENPCState2::Idle:
		IdleState();
		break;
	case ENPCState2::Walk:
		WalkState();
		break;
	}

	TArray<AActor*>objs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHelloFutureCharacter::StaticClass(), objs);
	for (AActor* actor : objs)
	{
		if (actor) target = actor;
	}


	FVector PlayerDir = target->GetActorLocation() - GetActorLocation();
	FRotator rot = PlayerDir.Rotation();

}

// Called to bind functionality to input
void AOh_MovingNPC2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOh_MovingNPC2::IdleState()
{
	currnetTime += GetWorld()->DeltaTimeSeconds;

	if (currnetTime > idleDelayTime)
	{
		m_state2 = ENPCState2::Walk;

		currnetTime = 0;

		randomPos = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), 1500);

		
	}



}

	void AOh_MovingNPC2::WalkState()
	{
		if (!ai) return;
		GetCharacterMovement()->MaxWalkSpeed = 100;

		//EPathFollowingRequestResult::Type r = ai->MoveToLocation(randomPos);

		// 랜덤 위치로 가자 
		if (ai->MoveToLocation(randomPos) == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			// 이동 가능한 랜덤위치 가져오기
			//randomPos = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), 1500);
			
			m_state2 = ENPCState2::Idle;

			currnetTime = 0;

			
		}

		
	}
