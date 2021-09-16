// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelloFutureGameMode.h"
#include "HelloFutureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHelloFutureGameMode::AHelloFutureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}



	//ohController = CreateDefaultSubobject<AOH_PlayerController>(TEXT("OH_PlayerController"));

}

