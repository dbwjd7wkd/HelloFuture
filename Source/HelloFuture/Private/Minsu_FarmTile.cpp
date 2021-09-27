// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_FarmTile.h"
#include <Components/TextRenderComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AMinsu_FarmTile::AMinsu_FarmTile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	SetRootComponent(bodyMesh);
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("StaticMesh'/Game/Minsu/Farm/Mesh/Minsu_FarmField.Minsu_FarmField'"));
	if (TempMesh.Succeeded())
	{
		bodyMesh->SetStaticMesh(TempMesh.Object);
	}

	countMesh = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Count Mesh"));
	countMesh->SetTextRenderColor(FColor::Black);
	countMesh->SetupAttachment(bodyMesh);
	countMesh->SetRelativeLocation(FVector(0, 0, 200.f));
	countMesh->SetHorizontalAlignment(EHTA_Center);
	countMesh->SetVerticalAlignment(EVRTA_TextCenter);
	countMesh->SetText(TEXT("..."));
	

	
}

// Called when the game starts or when spawned
void AMinsu_FarmTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinsu_FarmTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

