// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_Quiz_Next.h"

AMinsu_Quiz_Next::AMinsu_Quiz_Next()
{
	State = true;
	Intensity = 100000.f;
	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(RootComponent);
	Light->SetIntensity(Intensity);
}

void AMinsu_Quiz_Next::Interact()
{
	if (State)
	{
		Light->SetIntensity(0);
	}
	else
	{
		Light->SetIntensity(Intensity);
	}
	State = !State;
}

