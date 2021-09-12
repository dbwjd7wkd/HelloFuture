// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Oh_NPC.generated.h"

UCLASS()
class HELLOFUTURE_API AOh_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOh_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnyWhere, Category = Collision)
	class UCapsuleComponent* collision;

	//UPROPERTY(EditAnyWhere, Category = Body)
	//class USkeletalMeshComponent* body;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Time)
	float currnetTime = 0;

	UPROPERTY(EditAnywhere, Category = Time)
	float createTime = 5;

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




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		class UTextRenderComponent* talk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	class UWidgetComponent* talkWidget;

	void RandomTalk();
	void talkDelayFunc();
	
	class UMyTalkWidget* myTalk;

private:
};
