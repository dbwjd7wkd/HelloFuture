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
	fishingLoop,
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
	UFUNCTION(BlueprintCallable, Category = "TestFunctions")
		FString GetCurrentMapName();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
	EFishingState m_state;

	UPROPERTY()
	class AHelloFutureCharacter* me;

	UPROPERTY()
	class UFishingAnimInstance* anim;


	
	
	
	void IdleState();
	void StartState();
	void LoopState();
	void NibbleState();
	void BiteState();
	void EndState();

public:




	UPROPERTY(EditAnywhere, Category = "FSM")
	float fishingStartTime = 1.86;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float NibbleTime = 2;

	UPROPERTY()
	float currentTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		float LoopTime = 2;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float LoopTime2 = 3.5;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float LoopTime3 = 5;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float LoopTime4 = 6.5;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float LimitTime = 2;
	

	UPROPERTY(EditAnywhere, Category = "FSM")
		int32 BiteNumber = 0;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float BiteTime = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		bool NibbleMiss = false;

	UPROPERTY(EditAnywhere, Category = "FSM")
		bool BiteMiss = false;

	UPROPERTY(EditAnywhere, Category = "FSM")
		float EndTime = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		bool StartAnim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		bool LoopAnim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		bool NibbleAnim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		bool BiteAnim = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		bool EndAnim = false;

};
