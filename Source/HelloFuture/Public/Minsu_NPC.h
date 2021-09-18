// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Minsu_NPC.generated.h"

UCLASS()
class HELLOFUTURE_API AMinsu_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinsu_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// 	UPROPERTY(VisibleAnywhere, Category = "Sphere Comp")
// 		class USphereComponent* sphereComp;

// 	UPROPERTY(VisibleAnywhere, Category = NPCSettings)
// 		class AMinsu_Character* player;


public:
	UPROPERTY(EditAnywhere, Category = Time)
		float currnetTime = 0;

	UPROPERTY(EditAnywhere, Category = Time)
		float currnetTime2 = 0;

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

	UPROPERTY()
		class AActor* target;


// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
// 		class UTextRenderComponent* talkMinsu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		class UWidgetComponent* talkWidgetMinsu;

	void RandomTalk();
	void talkDelayFunc();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	class UMyTalkWidget* minsuTalk;

// 	UFUNCTION()
// 		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// 	
// 	UPROPERTY(VisibleAnywhere, Category = "Body Mesh")
// 		class USkeletalMeshComponent* bodyMesh;
// 
// 	UPROPERTY(VisibleAnywhere, Category = "Box Comp")
// 		class UBoxComponent* boxComp;
};
