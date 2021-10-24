// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Oh_windmill.generated.h"

UCLASS()
class HELLOFUTURE_API AOh_windmill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOh_windmill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UBoxComponent* collision;

	UPROPERTY(VisibleAnywhere, Category = "BodyMesh")
		class UStaticMeshComponent* bodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		FRotator Spin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		FVector Bob;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float BobSpeedMultiplier;

	UPROPERTY()
		FVector StartLocation;

};
