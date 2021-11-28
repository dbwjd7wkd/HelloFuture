// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Oh_FishingFSM.generated.h"


UENUM(BlueprintType)
enum class EFishingState : uint8
{
	Idle,
	fishingStart,
	fishingRoop,
	fishingNibble,
	fishingBite,
	fishingEnd
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOFUTURE_API UOh_FishingFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOh_FishingFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, Category = "FSM")
	EFishingState m_state;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "FSM")
	class AHelloFutureCharacter* me;


	
	void IdleState();
	void StartState();
	void RoopState();
	void NibbleState();
	void BiteState();
	void EndState();


	UPROPERTY(EditAnywhere, Category = "FSM")
	float fishingStartTime = 3;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float NibbleTime = 2;

	UPROPERTY()
	float currentTime = 0;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float LoopTime = 2;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float LoopTime2 = 3.5;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float LoopTime3 = 5;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float LoopTime4 = 6.5;
	
};
