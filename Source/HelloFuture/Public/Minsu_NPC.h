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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		class UWidgetComponent* talkWidget;

private:
	class UMyTalkWidget* myTalk;
	

// 	UFUNCTION()
// 		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// 	
// 	UPROPERTY(VisibleAnywhere, Category = "Body Mesh")
// 		class USkeletalMeshComponent* bodyMesh;
// 
// 	UPROPERTY(VisibleAnywhere, Category = "Box Comp")
// 		class UBoxComponent* boxComp;
};
