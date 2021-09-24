// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_DialLog.h"
#include "Kismet/GameplayStatics.h"
#include "HelloFutureCharacter.h"
#include "OH_PlayerController.h"
#include "OH_QuestUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
AYJ_DialLog::AYJ_DialLog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 다이얼로그 가져오기
	Dialogue = CreateDefaultSubobject<UDataTable>(TEXT("DataTable'/Game/YJ/Blueprints/DialLog_YJ.DialLog_YJ'"));
}

// Called when the game starts or when spawned
void AYJ_DialLog::BeginPlay()
{
	Super::BeginPlay();
	
	// 플레이어컨트롤러 가져오기
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (*Iterator != nullptr)
		{
			//curPlayerController->oh_QuestUI->InitializeDialogue(Dialogue);
			curPlayerController = Cast<AOH_PlayerController>(*Iterator);

			if (curPlayerController == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("AOH_PlayerController 가져오지 못함!!"));
				return;
			}

			break;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("플레이어 컨트롤러 없음!!"));
			return;
		}
	}

	//curPlayerController = Cast<AOH_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); //실패
	//curPlayerController = Cast<AOH_PlayerController>(Cast<AHelloFutureCharacter>(GetOwner())->GetController()); //실패

	if (curPlayerController != nullptr && Dialogue != nullptr)
	{
		//curPlayerController->oh_QuestUI->InitializeDialogue(Dialogue); //InitializeDialogue 함수에서 걸림!!
		UE_LOG(LogTemp, Warning, TEXT("GOOD!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BAD!!"));
	}


}

// Called every frame
void AYJ_DialLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}