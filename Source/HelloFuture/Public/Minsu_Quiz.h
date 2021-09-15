// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minsu_Quiz.generated.h"

UCLASS()
class HELLOFUTURE_API AMinsu_Quiz : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinsu_Quiz();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = QuizSettings)
		class UCapsuleComponent* capsuleCollision;

	UPROPERTY(VisibleAnywhere, Category = QuizSettings)
		class AHelloFutureCharacter* player;
};
