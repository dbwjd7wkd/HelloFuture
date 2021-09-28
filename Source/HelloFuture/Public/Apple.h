// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple.generated.h"

UCLASS()
class HELLOFUTURE_API AApple : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AApple();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	



	UPROPERTY(EditAnyWhere, Category = Collision)
	class UCapsuleComponent* collision;



	UPROPERTY(EditAnyWhere, Category = Body)
	class UStaticMeshComponent* body;


private:

	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void EndOverlap(UPrimitiveComponent* overlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		class UTextRenderComponent* price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " UI")
	TSubclassOf <UUserWidget> ui;	

	UPROPERTY()
	class UUserWidget* purchaseUI;

	UPROPERTY()
	class AOH_PlayerController* playercontroller;

	UPROPERTY()
	class AHelloFutureCharacter* character;

	
	void Interact();
	bool beginoverlaped;

};
