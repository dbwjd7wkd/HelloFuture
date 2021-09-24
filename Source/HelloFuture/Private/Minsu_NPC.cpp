// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_NPC.h"
/*#include <Components/SkeletalMeshComponent.h>*/
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>
#include <Math/UnrealMathUtility.h>
#include "Components/TextRenderComponent.h"
/*#include <Minsu_Character.h>*/
/*#include <Components/BoxComponent.h>*/
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyTalkWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Minsu_Character.h>
#include <Components/SceneComponent.h>
#include <HelloFutureCharacter.h>

// Sets default values
AMinsu_NPC::AMinsu_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

// 	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
// 	sphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
// 	sphereComp->SetRelativeScale3D(FVector(6, 6, 6));
// 	SetRootComponent(capsuleComp);
// 	
// 
// 	bodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body Mesh"));
// 	bodyMesh->SetupAttachment(RootComponent);
// 
// 	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
// 	boxComp->SetupAttachment(RootComponent);
	talkWidgetMinsu = CreateDefaultSubobject<UWidgetComponent>(TEXT("Talk Widget"));
	talkWidgetMinsu->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	/*talkWidget->SetupAttachment(RootComponent);*/
}

// Called when the game starts or when spawned
void AMinsu_NPC::BeginPlay()
{
	Super::BeginPlay();

	minsuTalk = Cast<UMyTalkWidget>(talkWidgetMinsu->GetWidget());

	FTimerHandle randomTalkTimer;
	GetWorld()->GetTimerManager().SetTimer(randomTalkTimer, this, &AMinsu_NPC::RandomTalk, delayTime, true);

	// myTalk->Text_Talk->SetText(FText::FromString(TEXT("안녕")));
/*	player = Cast<AMinsu_Character>(GetOwner());*/

/*	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMinsu_NPC::OnOverlapBegin);*/
}

// Called every frame
void AMinsu_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
	talkWidgetMinsu->SetWorldRotation(FRotator(GetActorRotation().Pitch, rot.Yaw, rot.Roll));


}

// Called to bind functionality to input
void AMinsu_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMinsu_NPC::RandomTalk()
{
	FTimerHandle talkdelayTimer;
	GetWorld()->GetTimerManager().SetTimer(talkdelayTimer, this, &AMinsu_NPC::talkDelayFunc, 1.f, false, 4.f);


	// 랜덤 값을 구한다.
	int32 Precent = FMath::RandRange(1, 100);


	// 랜덤값에 맞게 문자 출력
	if (Precent <= Rate1)
	{
		minsuTalk->Text_Talk->SetText(FText::FromString(TEXT("구경하고 가세요~")));

	}
	else if (Rate1 <= Precent && Precent <= Rate2)
	{
		minsuTalk->Text_Talk->SetText(FText::FromString(TEXT("저축왕은 누구일까요?")));
	}
	else if (Rate2 <= Precent && Precent <= Rate3)
	{
		minsuTalk->Text_Talk->SetText(FText::FromString(TEXT("퀴즈도 참여해봐요!")));
	}
	else if (Rate3 <= Precent && Precent <= Rate4)
	{
		minsuTalk->Text_Talk->SetText(FText::FromString(TEXT("신문 보고가세요~")));
	}
}

void AMinsu_NPC::talkDelayFunc()
{
	minsuTalk->Text_Talk->SetText(FText::FromString(TEXT("")));
}

