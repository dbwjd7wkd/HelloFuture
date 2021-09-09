// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_MovingNPC.h"
#include <AIController.h>
#include <NavigationSystem.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyTalkWidget.h"
#include "Components/TextBlock.h"

// Sets default values
AOh_MovingNPC::AOh_MovingNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	talkWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Talk Widget"));
	talkWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AOh_MovingNPC::BeginPlay()
{
	Super::BeginPlay();
	

	ai = Cast<AAIController>(GetController());

	ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	m_state = ENPCState::Idle;
	
	myTalk = Cast<UMyTalkWidget>(talkWidget->GetWidget());

	

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


	// 시간이 흐른다.
	currnetTime2 += GetWorld()->DeltaTimeSeconds;


	// 시간이 생성시간을 지나면
	if (currnetTime2 > createTime)
	{
		// 랜덤 값을 구한다.
		int32 Precent = FMath::RandRange(1, 100);

		// 랜덤값에 맞게 문자 출력
		if (Precent <= Rate1)
		{
			myTalk->Text_Talk->SetText(FText::FromString(TEXT(" 좋은 물건이 많군")));

		}
		else if (Rate1 <= Precent && Precent <= Rate2)
		{
			myTalk->Text_Talk->SetText(FText::FromString(TEXT("맛있어 보이는걸..")));
		}
		else if (Rate2 <= Precent && Precent <= Rate3)
		{
			myTalk->Text_Talk->SetText(FText::FromString(TEXT("저 아가씨 이쁜걸?")));
		}
		else //if (Rate3 <= Precent && Precent <= Rate4)
		{
			myTalk->Text_Talk->SetText(FText::FromString(TEXT("바쁘다 바빠")));
		}
		/*else if (Rate4 <= Precent && Precent <= Rate5)
		{
			myTalk->Text_Talk->SetText(FText::FromString(TEXT(" ")));
		}
		else if (Rate5 <= Precent && Precent <= Rate6)
		{
			myTalk->Text_Talk->SetText(FText::FromString(TEXT(" ")));
		}
		else
		{
			myTalk->Text_Talk->SetText(FText::FromString(TEXT(" ")));

		}*/

		// 문자 출력 후 현재시간 초기화
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

		randomPos = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), 1000);
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

