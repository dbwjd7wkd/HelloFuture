// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minsu_NoticeBoard.generated.h"

UCLASS()
class HELLOFUTURE_API AMinsu_NoticeBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinsu_NoticeBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "BodyMesh")
	class UStaticMeshComponent* bodyMesh;
	

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* collision;

	UPROPERTY(VisibleAnywhere, Category = "Newspaper")
	class UStaticMeshComponent* newspaper;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* NScollision;

	UPROPERTY(VisibleAnywhere, Category = "JCKing")
	class UStaticMeshComponent* JCKing;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* JKcollision;

	UPROPERTY(VisibleAnywhere, Category = "Quiz")
	class UStaticMeshComponent* quiz;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* QZcollision;
};
