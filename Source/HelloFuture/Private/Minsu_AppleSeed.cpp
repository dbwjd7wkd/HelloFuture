// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_AppleSeed.h"

// Sets default values
AMinsu_AppleSeed::AMinsu_AppleSeed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	SetRootComponent(bodyMesh);
}

// Called when the game starts or when spawned
void AMinsu_AppleSeed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinsu_AppleSeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

