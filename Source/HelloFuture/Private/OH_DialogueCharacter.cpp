// Fill out your copyright notice in the Description page of Project Settings.


#include "OH_DialogueCharacter.h"

// Sets default values
AOH_DialogueCharacter::AOH_DialogueCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOH_DialogueCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOH_DialogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOH_DialogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

