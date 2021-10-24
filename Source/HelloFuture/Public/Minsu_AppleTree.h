// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minsu_ShakeTree.h"
#include "Minsu_AppleTree.generated.h"

UCLASS()
class HELLOFUTURE_API AMinsu_AppleTree : public AActor, public IMinsu_ShakeTree
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinsu_AppleTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
		class UStaticMeshComponent* bodyMesh;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
		class UBillboardComponent* billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		TSubclassOf<class AActor> fruits;

	UFUNCTION(BlueprintCallable, Category = "Stat")
		void SpawnFruit();

	class AMinsu_AppleTree* me;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Farm)
		void ShakeTree();
	virtual void ShakeTree_Implementation() override;
	
	UPROPERTY()
		class AHelloFutureCharacter* player;
};
