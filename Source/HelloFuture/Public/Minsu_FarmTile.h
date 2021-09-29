// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minsu_Activate.h"
#include "Minsu_PlantSeed.h"
#include "Minsu_FarmTile.generated.h"

UCLASS()
class HELLOFUTURE_API AMinsu_FarmTile : public AActor, public IMinsu_Activate, public IMinsu_PlantSeed
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

	UPROPERTY()
		class AMinsu_FarmTile* me;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
		bool IsSomethingPlanted = false;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		FVector RelativeTransformLocation;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Farm)
		void Activate();
	virtual void Activate_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Farm)
		void PlantSeed();
	virtual void PlantSeed_Implementation() override;

	UPROPERTY()
		class AHelloFutureCharacter* player;

	UFUNCTION(BlueprintCallable, Category = Farm)
		void PlantApple();

	UPROPERTY(EditDefaultsOnly, Category = Farm)
		TSubclassOf<class AApple> appleFactory;

	UFUNCTION(BlueprintCallable, Category = Farm)
		void GrowTime(int growTime);

	UPROPERTY(EditAnywhere, Category = Farm)
		FText value;

	FTimerHandle DelayTimeHandle;

	void AdvanceTimer();

	int32 time;

	FText timeText;

	/*auto appleSeed = GetWorld()->SpawnActor<AApple>(appleFactory);*/
};
