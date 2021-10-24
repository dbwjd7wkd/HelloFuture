// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_windmill.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AOh_windmill::AOh_windmill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = collision;


	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	bodyMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AOh_windmill::BeginPlay()
{
	Super::BeginPlay();
	

	StartLocation = GetActorLocation();

}

// Called every frame
void AOh_windmill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//AddActorWorldRotation(Spin * DeltaTime);
	AddActorLocalRotation(Spin * (DeltaTime / 4));
	float time = GetWorld()->GetRealTimeSeconds();
	float sine = FMath::Sin(time * BobSpeedMultiplier);
	SetActorLocation(StartLocation + (Bob * sine));


}



