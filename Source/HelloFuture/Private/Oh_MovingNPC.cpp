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
#include <Engine/EngineTypes.h>
#include "Minsu_Character.h"
#include "HelloFutureCharacter.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AOh_MovingNPC::AOh_MovingNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	talkWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Talk Widget"));
	talkWidget->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	
}

// Called when the game starts or when spawned
void AOh_MovingNPC::BeginPlay()
{
	Super::BeginPlay();
	

	ai = Cast<AAIController>(GetController());

	ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	m_state = ENPCState::Idle;
	
	myTalk2 = Cast<UMyTalkWidget>(talkWidget->GetWidget());

	FTimerHandle randomTalkTimer;
	GetWorld()->GetTimerManager().SetTimer(randomTalkTimer, this, &AOh_MovingNPC::RandomTalk, delayTime, true);

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

	TArray<AActor*>objs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHelloFutureCharacter::StaticClass(), objs);
	for (AActor* actor : objs)
	{
		if (actor) target = actor;
	}


	// 시간이 흐른다.
	currnetTime2 += GetWorld()->DeltaTimeSeconds;

	FVector PlayerDir = target->GetActorLocation() - GetActorLocation();
	FRotator rot = PlayerDir.Rotation();
	talkWidget->SetWorldRotation(FRotator(GetActorRotation().Pitch, rot.Yaw, rot.Roll));




	
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
	if (!ai) return;
	GetCharacterMovement()->MaxWalkSpeed = 100;

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

void AOh_MovingNPC::RandomTalk()
{
	FTimerHandle talkdelayTimer;
	GetWorld()->GetTimerManager().SetTimer(talkdelayTimer, this, &AOh_MovingNPC::talkDelayFunc, 1.f, false, 4.f);


	// 랜덤 값을 구한다.
	int32 Precent = FMath::RandRange(1, 100);


	// 랜덤값에 맞게 문자 출력
	if (Precent <= Rate1)
	{
		myTalk2->Text_Talk->SetText(FText::FromString(TEXT("맛있어 보인다..")));

	}
	else if (Rate1 <= Precent && Precent <= Rate2)
	{
		myTalk2->Text_Talk->SetText(FText::FromString(TEXT("바쁘다 바빠!!")));
	}
	else if (Rate2 <= Precent && Precent <= Rate3)
	{
		myTalk2->Text_Talk->SetText(FText::FromString(TEXT("저리비켜!")));
	}
	else if (Rate3 <= Precent && Precent <= Rate4)
	{
		myTalk2->Text_Talk->SetText(FText::FromString(TEXT("사람이 많네..")));
	}
}

void AOh_MovingNPC::talkDelayFunc()
{
	myTalk2->Text_Talk->SetText(FText::FromString(TEXT("")));
}



