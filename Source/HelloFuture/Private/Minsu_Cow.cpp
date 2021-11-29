// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_Cow.h"
#include <AIController.h>
#include <NavigationSystem.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include <Engine/EngineTypes.h>
#include "HelloFutureCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>
#include <Blueprint/UserWidget.h>

// Sets default values
AMinsu_Cow::AMinsu_Cow()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	boxComp->SetupAttachment(RootComponent);
	boxComp->SetWorldLocation(FVector(115, 0, 0));
	/*boxComp->OnComponentBeginOverlap.AddDynamic(this, &AMinsu_Cow::OnTriggerEnter);*/
	boxComp->SetRelativeScale3D(FVector(2.5, 2.5, 2.5));
}

// Called when the game starts or when spawned
void AMinsu_Cow::BeginPlay()
{
	Super::BeginPlay();

	ai = Cast<AAIController>(GetController());

	ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	m_state = ECowState::Idle;
}

// Called every frame
void AMinsu_Cow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (m_state)
	{
	case ECowState::Idle:
		IdleState();
		break;
	case ECowState::Walk:
		WalkState();
		break;
	}

	TArray<AActor*>objs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHelloFutureCharacter::StaticClass(), objs);
	for (AActor* actor : objs)
	{
		if (actor) target = actor;
	}

	currnetTime2 += GetWorld()->DeltaTimeSeconds;

	FVector PlayerDir = target->GetActorLocation() - GetActorLocation();
	FRotator rot = PlayerDir.Rotation();
}

// Called to bind functionality to input
void AMinsu_Cow::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMinsu_Cow::IdleState()
{
	currnetTime += GetWorld()->DeltaTimeSeconds;

	if (currnetTime > idleDelayTime)
	{
		m_state = ECowState::Walk;

		currnetTime = 0;

		randomPos = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), 1000);
	}
}

void AMinsu_Cow::WalkState()
{
	if (!ai) return;
	GetCharacterMovement()->MaxWalkSpeed = 100;


	if (ai->MoveToLocation(randomPos) == EPathFollowingRequestResult::AlreadyAtGoal)
	{

		m_state = ECowState::Idle;

		currnetTime = 0;
	}
}

//void AMinsu_Cow::OnTriggerEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (AnimalUI == nullptr)
//	{
//		AnimalUI = CreateWidget<UUserWidget>(GetWorld(), AnimalUIFactory);
//	}
//
//	if (AnimalUI)
//	{
//		AnimalUI->AddToViewport();
//	}
//
//}
