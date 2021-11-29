// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Minsu_Cow.generated.h"

UENUM(BlueprintType)
enum class ECowState : uint8
{
	Idle,
	Walk,
	TurnLeft,
	TurnRight,
	Sleep,
	Feed
};

UCLASS()
class HELLOFUTURE_API AMinsu_Cow : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinsu_Cow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = FSM, BlueprintReadWrite)
		ECowState m_state;

	UPROPERTY(EditAnywhere, Category = Time)
		float currentTime = 0;

	/*UPROPERTY(EditAnywhere, Category = Time)
		float currentTime2 = 0;*/

	UPROPERTY(EditAnywhere, Category = Time)
		float createTime = 8;

	UPROPERTY(EditAnywhere, Category = FSM)
		float idleDelayTime = 2;

	UPROPERTY(EditAnywhere, Category = Time)
		float delayTime = 9;

	UPROPERTY(EditAnywhere, Category = Time)
		float sleepTime = 3;

	UPROPERTY(EditAnywhere, Category = Time)
		float feedTime = 3.4;

	UPROPERTY()
		class AAIController* ai;

	UPROPERTY()
		FVector randomPos;

	UPROPERTY()
		class UNavigationSystemV1* ns;

	UPROPERTY()
		class AActor* target;

	UPROPERTY(EditAnywhere, Category = BoxComp)
		class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUserWidget> AnimalUIFactory;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		class UUserWidget* AnimalUI;

	UPROPERTY(EditAnywhere, Category = Setting)
		float speed;

	UPROPERTY(EditAnywhere, Category = Setting)
		float direction;

private:
	void IdleState();
	void WalkState();
	void SleepState();
	void FeedState();
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
