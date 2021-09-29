// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"
#include "OH_PlayerController.h"
#include "HelloFutureCharacter.h"
#include <Components/BoxComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/TextRenderComponent.h>
#include <Blueprint/UserWidget.h>
#include <GameFramework/Actor.h>
#include <GameFramework/PlayerController.h>

// Sets default values
AApple::AApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = collision;


	//collision2 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision2"));

	collision->OnComponentBeginOverlap.AddDynamic(this, &AApple::BeginOverlap);
	collision->OnComponentEndOverlap.AddDynamic(this, &AApple::EndOverlap);


	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bpdy"));
	body->SetupAttachment(collision);


	price = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Price"));
	price ->SetTextRenderColor(FColor::Black);
	price->SetupAttachment(body);


	//beginoverlaped = false;


}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();

	/*price -> SetVisibility(false);
	if(ui)
	{ 

	purchaseUI = CreateWidget<UUserWidget>(GetWorld(), ui);

	}*/
	
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	

}



void AApple::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult)
{
	//beginoverlaped =true;

	//price -> SetVisibility(true);

	//if(purchaseUI)
	//{ 
	//	//playercontroller->SetInputMode(FInputModeUIOnly());
	//	
	//	purchaseUI->AddToViewport();

	//}

}

void AApple::EndOverlap(UPrimitiveComponent* overlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//beginoverlaped = false;

	//price->SetVisibility(false);

	//purchaseUI->RemoveFromParent();

}

void AApple::Interact()
{
	//beginoverlaped = true;



}



