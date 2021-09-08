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
	talk->SetupAttachment(GetCapsuleComponent());
	
	talkWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Talk Widget"));
	talkWidget->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AOh_NPC::BeginPlay()
{
	Super::BeginPlay();
	
	myTalk = Cast<UMyTalkWidget>(talkWidget->GetWidget());
}

// Called every frame
void AOh_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		myTalk->Text_Talk->SetText(FText::FromString("안녕"));
	
	// 시간이 흐른다.
	//currnetTime += GetWorld()->DeltaTimeSeconds;

	//
	//// 시간이 생성시간을 지나면
	//if (currnetTime > createTime )
	//{
	//	// 랜덤 값을 구한다.
	//	int32 Precent = FMath::RandRange(1, 100);
	//	
	//		// 랜덤값에 맞게 문자 출력
	//		if (Precent <= Rate1)
	//		{
	//			talk->SetText(FText::FromString("안녕"));

	//			//UE_LOG(LogTemp, Warning, TEXT("맛좋은 사과있어요~"));
	//			//FString chat = FString::Printf(TEXT("Hi"));
	//		}
	//		else if (Rate1 <= Precent && Precent <= Rate2)
	//		{
	//			talk->SetText(FText::FromString("Hi"));
	//			
	//			//UE_LOG(LogTemp, Warning, TEXT("쌉니다 싸!"));
	//			//FString chat2 = FString::Printf(TEXT("2"));
	//		}
	//		else if (Rate2 <= Precent && Precent <= Rate3)
	//		{
	//			talk->SetText(FText::FromString("hello"));
	//			
	//			//UE_LOG(LogTemp, Warning, TEXT("충주사과 있습니다~"));
	//			//FString chat3 = FString::Printf(TEXT("3"));
	//		}
	//		else if (Rate3 <= Precent && Precent <= Rate4)
	//		{
	//			talk->SetText(FText::FromString("오쌍"));
	//			
	//			//FString chat3 = FString::Printf(TEXT("3"));
	//		}
	//		else if (Rate4 <= Precent && Precent <= Rate5)
	//		{
	//			talk->SetText(FText::FromString(" "));

	//			//FString chat3 = FString::Printf(TEXT("3"));
	//		}
	//		else if (Rate5 <= Precent && Precent <= Rate6)
	//		{
	//			talk->SetText(FText::FromString(" "));

	//			//FString chat3 = FString::Printf(TEXT("3"));
	//		}
	//		else
	//		{
	//			talk->SetText(FText::FromString(" "));

	//			//UE_LOG(LogTemp, Warning, TEXT("자자 골라골라 ^~^"));
	//			//FString chat4 = FString::Printf(TEXT("4"));
	//		}

	//		// 문자 출력 후 현재시간 초기화
	//		currnetTime = 0;
	//	
	//	return;
	//}





	/*else if (currnetTime > createTime && currnetTime > talkTime)
	{
		talk->SetText(FText::FromString(" "));
	}*/
	/*else if (currnetTime > createTime && currnetTime > talkTime)
	{
		currnetTime = 0;
	}*/

}

// Called to bind functionality to input
void AOh_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

