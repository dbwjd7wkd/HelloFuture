// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"
#include <Components/BoxComponent.h>
#include <Components/CapsuleComponent.h>

// Sets default values
AApple::AApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = collision;

	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bpdy"));
	body->SetupAttachment(collision);



}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

