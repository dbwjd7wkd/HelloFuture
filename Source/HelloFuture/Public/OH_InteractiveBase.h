// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OH_InteractiveBase.generated.h"

UCLASS()
class HELLOFUTURE_API AOH_InteractiveBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOH_InteractiveBase();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive)
	class USceneComponent* rootScence;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive)
	class UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive)
	class USceneComponent* lookAtPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive)
	class UBoxComponent* collision;

public:
	UPROPERTY(EditDefaultsOnly, Category = Interactive)
	bool bCanLookAt = true;

	FORCEINLINE USceneComponent* GetLookAtPoint(){ return lookAtPoint;}

	FORCEINLINE bool CanLookAt() {return bCanLookAt;}

	UPROPERTY()
	class AHelloFutureCharacter* currentCharacter;

	UPROPERTY()
	class AOH_PlayerController* currentPlayerController;

	UPROPERTY()
	class UOH_QuestUI* oh_QuestUI;

	TSubclassOf<class UUserWidget> oh_QuestUIclass;

	FORCEINLINE UOH_QuestUI* GetUI() { return oh_QuestUI; };

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
		class UDataTable* Dialogue2;*/

private:
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* overlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	bool bIsEnabled;

public:
	virtual void BeginPlay() override;

	virtual void SetEnable(bool Enable);

	virtual void Interact();


};
