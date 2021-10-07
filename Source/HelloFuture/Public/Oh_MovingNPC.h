// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Oh_MovingNPC.generated.h"

UENUM(BlueprintType)
enum class ENPCState : uint8
{
	Idle,
	Walk
};

UCLASS()
class HELLOFUTURE_API AOh_MovingNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOh_MovingNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = FSM, BlueprintReadWrite)
		ENPCState m_state;

	UPROPERTY(EditAnywhere, Category = Time)
		float currnetTime = 0;

	UPROPERTY(EditAnywhere, Category = Time)
		float currnetTime2 = 0;

	UPROPERTY(EditAnywhere, Category = Time)
		float createTime = 8;

	UPROPERTY(EditAnywhere, Category = FSM)
		float idleDelayTime = 2;

	UPROPERTY(EditAnywhere, Category = Time)
		float delayTime = 9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		int32 Rate1 = 25;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		int32 Rate2 = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		int32 Rate3 = 75;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		int32 Rate4 = 100;

	UPROPERTY()
		class AAIController* ai;

	UPROPERTY()
		FVector randomPos;

	UPROPERTY()
		class UNavigationSystemV1* ns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		class UTextRenderComponent* talk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		class UWidgetComponent* talkWidget;
	
	UPROPERTY()
	class AActor* target;


private:
	class UMyTalkWidget* myTalk2;
	


private:
	void IdleState();
	void WalkState();
	void RandomTalk();
	void talkDelayFunc();
	
};
