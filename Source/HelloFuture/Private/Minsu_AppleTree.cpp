// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_AppleTree.h"
#include <Components/BillboardComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/Actor.h>

// Sets default values
AMinsu_AppleTree::AMinsu_AppleTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT ("Body Mesh"));
	SetRootComponent(bodyMesh);

	billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	billboard->SetupAttachment(bodyMesh);
}

// Called when the game starts or when spawned
void AMinsu_AppleTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinsu_AppleTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// ������ ����Ʈ����.
// ���ǻóĳ���Ϳ��� ����Ʈ���̽��� ��� �����ϰ�ʹ�.
void AMinsu_AppleTree::SpawnFruit()
{
	// ȸ������ �׻� ��������.
	float randomRotation = FMath::RandRange(0.f, 360.f);
	
	if (fruits)
	{
		UWorld* world = GetWorld();
	
		if (world)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FRotator rotator;
			rotator.Pitch = randomRotation;
			rotator.Yaw = randomRotation;
			rotator.Roll = randomRotation;
			FVector SpawnLocation = billboard->GetComponentLocation();

			world->SpawnActor<AActor>(fruits, SpawnLocation, rotator, SpawnParams);
		}
	}
}

void AMinsu_AppleTree::ShakeTree_Implementation()
{
	SpawnFruit();
}

