// Fill out your copyright notice in the Description page of Project Settings.


#include "OH_InteractiveBase.h"
#include "HelloFutureCharacter.h"
#include "OH_PlayerController.h"
#include "OH_QuestUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>


// Sets default values
AOH_InteractiveBase::AOH_InteractiveBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootScence = CreateDefaultSubobject<USceneComponent>(TEXT("RootScence"));
	RootComponent = rootScence;

	mesh =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(rootScence);

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	collision->SetupAttachment(rootScence);

	collision->OnComponentBeginOverlap.AddDynamic(this, &AOH_InteractiveBase::BeginOverlap);
	collision->OnComponentEndOverlap.AddDynamic(this, &AOH_InteractiveBase::EndOverlap);



}
// Called when the game starts or when spawned
void AOH_InteractiveBase::BeginPlay()
{
	Super::BeginPlay();
	
	//bIsEnabled =true;
}



void AOH_InteractiveBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning ,TEXT("DDD"));
	oh_QuestUI->AddToViewport();
	currentPlayerController->GetUI()->InitializeDialogue(Dialogue2);
	
	
	
	/*if(!bIsEnabled) return;

	currentCharacter = Cast<AHelloFutureCharacter>(OtherActor);

	if (currentCharacter)
	{
		currentPlayerController = Cast<AOH_PlayerController>(currentCharacter->GetController());



	}*/
}

void AOH_InteractiveBase::EndOverlap(UPrimitiveComponent* overlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if(bIsEnabled) return;

	currentCharacter = Cast<AHelloFutureCharacter>(OtherActor);

	if (currentCharacter)
	{
		
		currentPlayerController =nullptr;
	}*/
}


void AOH_InteractiveBase::SetEnable(bool Enable)
{
	/*bIsEnabled =Enable;
	
	if (bIsEnabled)
	{
		collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}*/
}

void AOH_InteractiveBase::Interact()
{
	//if(!bIsEnabled) return;
}

// Called every frame
void AOH_InteractiveBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

