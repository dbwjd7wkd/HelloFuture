// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minsu_FarmTile.generated.h"

UCLASS()
class HELLOFUTURE_API AMinsu_FarmTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinsu_FarmTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Mesh)
		class UStaticMeshComponent* bodyMesh;

	UPROPERTY(EditAnywhere, Category = Mesh)
		class UTextRenderComponent* countMesh;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		bool IsSomethingPlanted = false;
};
