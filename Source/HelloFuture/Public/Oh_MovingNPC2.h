// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Oh_MovingNPC2.generated.h"


UENUM(BlueprintType)
enum class ENPCState2 : uint8
{
	Idle,
	Walk
};


UCLASS()
class HELLOFUTURE_API AOh_MovingNPC2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOh_MovingNPC2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category = FSM, BlueprintReadWrite)
		ENPCState2 m_state2;

	UPROPERTY(EditAnywhere, Category = Time)
		float currnetTime = 0;

	UPROPERTY(EditAnywhere, Category = FSM)
		float idleDelayTime = 2;

	UPROPERTY()
		class AOH_InteractiveDialogue3* Dialogue3;


	UPROPERTY()
		class AAIController* ai;

	UPROPERTY()
		FVector randomPos;

	UPROPERTY()
		class UNavigationSystemV1* ns;


	UPROPERTY()
		class AActor* target;


private:
	void IdleState();
	void WalkState();


};
