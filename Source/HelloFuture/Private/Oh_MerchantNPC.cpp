// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_MerchantNPC.h"
#include <Components/CapsuleComponent.h>
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyTalkWidget.h"
#include "Components/TextBlock.h"


// Sets default values
AOh_MerchantNPC::AOh_MerchantNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	talkWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Talk Widget"));
	talkWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AOh_MerchantNPC::BeginPlay()
{
	Super::BeginPlay();
	
	myTalk = Cast<UMyTalkWidget>(talkWidget->GetWidget());

	FTimerHandle randomTalkTimer;
	GetWorld()->GetTimerManager().SetTimer(randomTalkTimer, this, &AOh_MerchantNPC::RandomTalk, delayTime, true);

}

// Called every frame
void AOh_MerchantNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currnetTime += GetWorld()->DeltaTimeSeconds;
}

// Called to bind functionality to input
void AOh_MerchantNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOh_MerchantNPC::RandomTalk()
{
	
	FTimerHandle talkdelayTimer;
	GetWorld()->GetTimerManager().SetTimer(talkdelayTimer, this, &AOh_MerchantNPC::talkDelayFunc, 1.f, false, 3.5f);


	// 랜덤 값을 구한다.
	int32 Precent = FMath::RandRange(1, 100);


	// 랜덤값에 맞게 문자 출력
	if (Precent <= Rate1)
	{
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("어서오세요 손님")));

	}
	else if (Rate1 <= Precent && Precent <= Rate2)
	{
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("모든 물건 매입합니다~")));
	}
	else if (Rate2 <= Precent && Precent <= Rate3)
	{
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("대량 구매 합니다!")));
	}
	else if (Rate3 <= Precent && Precent <= Rate4)
	{
		myTalk->Text_Talk->SetText(FText::FromString(TEXT("자자 한번 들려주세요")));
	}
}

void AOh_MerchantNPC::talkDelayFunc()
{
	myTalk->Text_Talk->SetText(FText::FromString(TEXT("")));
}

