// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minsu_Chair.generated.h"

UCLASS()
class HELLOFUTURE_API AMinsu_Chair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinsu_Chair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Body")
		class UStaticMeshComponent* bodyMesh;

	UPROPERTY(EditAnywhere, Category = "Collision")
		class UBoxComponent* collision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool")
		bool isSit = false;
};
