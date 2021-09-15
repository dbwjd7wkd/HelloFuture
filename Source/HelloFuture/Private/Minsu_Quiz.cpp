// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_Quiz.h"
#include <HelloFutureCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>
#include <Blueprint/UserWidget.h>
#include "Components/SceneComponent.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
AMinsu_Quiz::AMinsu_Quiz()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(_RootComponent);

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	bodyMesh->SetupAttachment(RootComponent);

	capsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	capsuleCollision->SetRelativeScale3D(FVector(0.818254, -0.929342, 1.739063));
}

// Called when the game starts or when spawned
void AMinsu_Quiz::BeginPlay()
{
	Super::BeginPlay();

/*	player = Cast<AHelloFutureCharacter>(GetOwner());*/
}

// Called every frame
void AMinsu_Quiz::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


// 
// 	TArray<AActor*> objs;
// 
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHelloFutureCharacter::StaticClass(), objs);
// 	for (AActor* actor : objs)
// 	{
// 		if (actor)
// 		{
// 			player = actor;
// 		}
// 	}
}


// void AMinsu_Quiz::SolveQuiz()
// {
// 	quizAlert->AddToViewport(0);
// }

