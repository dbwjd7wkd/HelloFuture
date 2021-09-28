// Fill out your copyright notice in the Description page of Project Settings.


#include "Oh_MerchantNPC.h"

// Sets default values
AOh_MerchantNPC::AOh_MerchantNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOh_MerchantNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOh_MerchantNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOh_MerchantNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

