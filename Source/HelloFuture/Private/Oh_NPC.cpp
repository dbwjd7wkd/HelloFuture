// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_NPC.h"
#include <Components/CapsuleComponent.h>
#include <Math/UnrealMathUtility.h>

// Sets default values
AOh_NPC::AOh_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	//RootComponent = collision;

	//body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	//body->SetupAttachment(collision);




}

// Called when the game starts or when spawned
void AOh_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOh_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	currnetTime += GetWorld()->DeltaTimeSeconds;

	if (currnetTime > createTime)
	{

		int32 Precent = FMath::RandRange(1, 100);

		if (Precent <= Rate1)
		{
			UE_LOG(LogTemp, Warning, TEXT("맛좋은 사과있어요~"));
			//FString chat = FString::Printf(TEXT("Hi"));
		}
		else if (Rate1 <= Precent && Precent <= Rate2)
		{
			UE_LOG(LogTemp, Warning, TEXT("쌉니다 싸!"));
			//FString chat2 = FString::Printf(TEXT("2"));
		}
		else if (Rate2 <= Precent && Precent <= Rate3)
		{
			UE_LOG(LogTemp, Warning, TEXT("충주사과 있습니다~"));
			//FString chat3 = FString::Printf(TEXT("3"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("자자 골라골라 ^~^"));
			//FString chat4 = FString::Printf(TEXT("4"));
		}

		currnetTime = 0;
		return;
	}
}

// Called to bind functionality to input
void AOh_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

