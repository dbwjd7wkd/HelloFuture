// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_NPC.h"
#include <Components/CapsuleComponent.h>
#include <Math/UnrealMathUtility.h>
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyTalkWidget.h"
#include "Components/TextBlock.h"

// Sets default values
AOh_NPC::AOh_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	//RootComponent = collision;

	//body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	//body->SetupAttachment(collision);

	talk = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Talk"));
	//talk->SetupAttachment(GetCapsuleComponent());
	talk->SetTextRenderColor(FColor::Black);
	
	
	
	talkWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Talk Widget"));
	talkWidget->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AOh_NPC::BeginPlay()
{
	Super::BeginPlay();
	
	myTalk = Cast<UMyTalkWidget>(talkWidget->GetWidget());

	FTimerHandle randomTalkTimer;
	GetWorld()->GetTimerManager().SetTimer(randomTalkTimer, this, &AOh_NPC::RandomTalk, delayTime, true);
	
}

// Called every frame
void AOh_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
 	// 시간이 흐른다.
	currnetTime += GetWorld()->DeltaTimeSeconds;

	
 	/*
 	// 시간이 생성시간을 지나면
 	if (currnetTime > createTime )
 	{
 		// 랜덤 값을 구한다.
 		int32 Precent = FMath::RandRange(1, 100);
 		
 		// 랜덤값에 맞게 문자 출력
 		if (Precent <= Rate1)
 		{
            myTalk->Text_Talk->SetText(FText::FromString(TEXT("어서오세요 손님")));
 				
 		}
 		else if (Rate1 <= Precent && Precent <= Rate2)
 		{
            myTalk->Text_Talk->SetText(FText::FromString(TEXT("쌉니다 싸~")));
 		}
 		else if (Rate2 <= Precent && Precent <= Rate3)
 		{
            myTalk->Text_Talk->SetText(FText::FromString(TEXT("신선한 사과 있습니다!")));
 		}
 		else if (Rate3 <= Precent && Precent <= Rate4)
 		{
            myTalk->Text_Talk->SetText(FText::FromString(TEXT("충주사과 있어요^~^")));
 		}
 		else if (Rate4 <= Precent && Precent <= Rate5)
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

 		}
 
 		// 문자 출력 후 현재시간 초기화
 		currnetTime = 0;
 		
 		return;
 	}
	*/


}

// Called to bind functionality to input
void AOh_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOh_NPC::RandomTalk()
{
	FTimerHandle talkdelayTimer;
	GetWorld()->GetTimerManager().SetTimer(talkdelayTimer, this, &AOh_NPC::talkDelayFunc, 1.f, false, 4.f);


	// 랜덤 값을 구한다.
	int32 Precent = FMath::RandRange(1, 100);


	// 랜덤값에 맞게 문자 출력
	if (Precent <= Rate1)
	{
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("어서오세요 손님")));

	}
	else if (Rate1 <= Precent && Precent <= Rate2)
	{
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("쌉니다 싸~")));
	}
	else if (Rate2 <= Precent && Precent <= Rate3)
	{
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("신선한 사과 있습니다!")));
	}
	else if (Rate3 <= Precent && Precent <= Rate4)
	{
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("충주사과 있어요^~^")));
	}


}

void AOh_NPC::talkDelayFunc()
{
\
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("")));

}

