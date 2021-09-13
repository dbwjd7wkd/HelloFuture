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
	talkWidgetMinsu->SetupAttachment(RootComponent);
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



}

// Called to bind functionality to input
void AMinsu_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMinsu_NPC::RandomTalk()
{

}

void AMinsu_NPC::talkDelayFunc()
{

}

