// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_NoticeBoard.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Materials/Material.h>
#include <UObject/ConstructorHelpers.h>

// Sets default values
AMinsu_NoticeBoard::AMinsu_NoticeBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	bodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = bodyMesh;

	// 	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("StaticMesh'/Game/Import/Village/Meshes/Props/TB_Prop_NoticeBoard_TB_Prop_NoticeBoard_226.TB_Prop_NoticeBoard_TB_Prop_NoticeBoard_226'"));
	// 	if (TempMesh.Succeeded())
	// 	{
	// 		bodyMesh->SetStaticMesh(TempMesh.Object);
	// 	}



	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	collision->SetupAttachment(bodyMesh);
	collision->SetRelativeLocation(FVector(-0.000031, 4.171566, 143.619522));
	collision->SetRelativeScale3D(FVector(5.574658, 0.750000, 5.250745));
	collision->SetCollisionProfileName(TEXT("BlockAll"));

	newspaper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Newspaper"));
	newspaper->SetupAttachment(bodyMesh);
	newspaper->SetRelativeLocation(FVector(84.867004, 27.666519, 208.300995));
	newspaper->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	newspaper->SetRelativeScale3D(FVector(0.6, 0.6, 0.6));
	// 	ConstructorHelpers::FObjectFinder<UStaticMesh>newsMesh(TEXT("StaticMesh'/Game/Minsu/Board/SM_NewsPaper.SM_NewsPaper'"));
	// 	if (newsMesh.Succeeded())
	// 	{
	// 		newspaper->SetStaticMesh(newsMesh.Object);
	// 	}

	JCKing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JCKing"));
	JCKing->SetupAttachment(bodyMesh);
	JCKing->SetRelativeLocation(FVector(-3.151077, 27.188330, 197.812576));
	JCKing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	JCKing->SetRelativeScale3D(FVector(0.7, 0.7, 0.7));
	// 	ConstructorHelpers::FObjectFinder<UStaticMesh>JKMesh(TEXT("StaticMesh'/Game/Minsu/Board/SM_JCKing.SM_JCKing'"));
	// 	if (JKMesh.Succeeded())
	// 	{
	// 		JCKing->SetStaticMesh(JKMesh.Object);
	// 	}

	quiz = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Quiz"));
	quiz->SetupAttachment(bodyMesh);
	quiz->SetRelativeLocation(FVector(-85.144737, 26.314939, 192.604736));
	quiz->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	quiz->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	// 	ConstructorHelpers::FObjectFinder<UStaticMesh>QZmesh(TEXT("StaticMesh'/Game/Minsu/Board/SM_Quiz.SM_Quiz'"));
	// 	if (QZmesh.Succeeded())
	// 	{
	// 		quiz->SetStaticMesh(QZmesh.Object);
	// 	}
}
// Called when the game starts or when spawned
void AMinsu_NoticeBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinsu_NoticeBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

