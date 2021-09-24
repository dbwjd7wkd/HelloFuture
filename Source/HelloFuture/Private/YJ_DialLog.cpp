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

	// ���̾�α� ��������
	Dialogue = CreateDefaultSubobject<UDataTable>(TEXT("DataTable'/Game/YJ/Blueprints/DialLog_YJ.DialLog_YJ'"));
}

// Called when the game starts or when spawned
void AYJ_DialLog::BeginPlay()
{
	Super::BeginPlay();
	
	// �÷��̾���Ʈ�ѷ� ��������
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (*Iterator != nullptr)
		{
			//curPlayerController->oh_QuestUI->InitializeDialogue(Dialogue);
			curPlayerController = Cast<AOH_PlayerController>(*Iterator);

			if (curPlayerController == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("AOH_PlayerController �������� ����!!"));
				return;
			}

			break;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("�÷��̾� ��Ʈ�ѷ� ����!!"));
			return;
		}
	}

	//curPlayerController = Cast<AOH_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); //����
	//curPlayerController = Cast<AOH_PlayerController>(Cast<AHelloFutureCharacter>(GetOwner())->GetController()); //����

	if (curPlayerController != nullptr && Dialogue != nullptr)
	{
		//curPlayerController->oh_QuestUI->InitializeDialogue(Dialogue); //InitializeDialogue �Լ����� �ɸ�!!
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