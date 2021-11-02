// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_Chair.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
AMinsu_Chair::AMinsu_Chair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(bodyMesh);

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	collision->SetupAttachment(bodyMesh);

	/*for (int i = 1; ; i++)
	{
		Tags.Add("Chair_%d", i);
	}*/
}

// Called when the game starts or when spawned
void AMinsu_Chair::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinsu_Chair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

