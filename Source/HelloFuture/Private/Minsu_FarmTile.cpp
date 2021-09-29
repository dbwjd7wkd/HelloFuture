// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_FarmTile.h"
#include <Components/TextRenderComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <HelloFutureCharacter.h>
#include <Kismet/KismetTextLibrary.h>
#include <Components/SceneComponent.h>
#include <Minsu_AppleSeed.h>
#include <Apple.h>

// Sets default values
AMinsu_FarmTile::AMinsu_FarmTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	SetRootComponent(bodyMesh);
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("StaticMesh'/Game/Minsu/Farm/Mesh/Minsu_FarmField.Minsu_FarmField'"));
	if (TempMesh.Succeeded())
	{
		bodyMesh->SetStaticMesh(TempMesh.Object);
	}

	countMesh = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Count Mesh"));
	countMesh->SetTextRenderColor(FColor::Black);
	countMesh->SetupAttachment(bodyMesh);
	countMesh->SetRelativeLocation(FVector(0, 0, 200.f));
	countMesh->SetHorizontalAlignment(EHTA_Center);
	countMesh->SetVerticalAlignment(EVRTA_TextCenter);
	countMesh->SetText(TEXT("..."));
	

	
}

// Called when the game starts or when spawned
void AMinsu_FarmTile::BeginPlay()
{
	Super::BeginPlay();
	
	countMesh->SetText(value);
}

// Called every frame
void AMinsu_FarmTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinsu_FarmTile::Activate_Implementation()
{

}

void AMinsu_FarmTile::PlantSeed_Implementation()
{
	player = Cast<AHelloFutureCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsSomethingPlanted == false)
	{
		switch (player->Seed)
		{
		case 0:
			PlantApple();
			UE_LOG(LogTemp, Warning, TEXT("PlantApple"));
			IsSomethingPlanted = true;
			break;
		}
	}
}

void AMinsu_FarmTile::PlantApple()
{
	auto appleSeed = GetWorld()->SpawnActor<AApple>(appleFactory);
	
	/*RelativeTransformLocation = me->GetActorLocation() + FVector(0, 0, 0);*/

	// ÃÊ±â
	if (appleSeed)
	{
		appleSeed->SetActorLocation(RelativeTransformLocation);
		GrowTime(5);
	
		appleSeed->SetActorLocation(RelativeTransformLocation + FVector(0, 0, 100));

// 		appleSeed->SetActorLocation(me-> GetActorLocation + FVector(0, 0, 100));
// 		GrowTime(5);
// 
// 		appleSeed->SetActorLocation(me-> GetActorLocation + FVector(0, 0, 200));
	}
}

void AMinsu_FarmTile::GrowTime(int32 growTime)
{
	time = growTime;

	timeText = UKismetTextLibrary::Conv_IntToText(time);
	countMesh->SetText(timeText);
	countMesh->USceneComponent::SetVisibility(true);
	
	GetWorldTimerManager().SetTimer(DelayTimeHandle, this, &AMinsu_FarmTile::AdvanceTimer, 1.0f, true);
	
	/*appleSeed->SetActorLocation(RelativeTransformLocation) + FVector(0, 0, 100);*/


// 	
// 	float DelayTime = 1.0f;
// 
// 	GetWorld()->GetTimerManager().SetTimer(DelayTimeHandle, FTimerDelegate::CreateLambda([&]()
// 	{
// 		--time;
// 		countMesh->SetText(timeText);
// 		
// 	}), DelayTime, false);
// 
// 	
// 
// 
// 
// 
// 	if (time == 1)
// 	{
// 		countMesh->SetText(value);
// 		return;
// 	}
// 	else 
// 	{
// 		GetWorld()->GetTimerManager().SetTimer(DelayTimeHandle, FTimerDelegate::CreateLambda([&]()
// 		{
// 			time = time-1;
// 
// 		}), DelayTime, false);
// 		countMesh->SetText(timeText);
// 		return;
// 	}
}

void AMinsu_FarmTile::AdvanceTimer()
{
	--time;
	countMesh->SetText(timeText);
	if (time == 0)
	{
		GetWorldTimerManager().ClearTimer(DelayTimeHandle);
		countMesh->SetText(value);
	}

}

