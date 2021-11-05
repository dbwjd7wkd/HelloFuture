// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minsu_Video.generated.h"

UCLASS()
class HELLOFUTURE_API AMinsu_Video : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinsu_Video();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class UMediaPlayer* mediaPlayer;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class UMediaSource* source;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class USceneComponent* rootComp;

	//영상을 출력할 공간 필요
	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class UStaticMeshComponent* screenMesh;

	// 전달받은 소스를 플레이하는 역할
	void PlayVideo(UMediaSource* playSource);

	UPROPERTY(EditAnywhere, Category = VideoSettings)
		class UWidgetComponent* buttonWidgetComp;

	// 전달받은 소스를 플레이하는 역할
	void BackVideo();
	void ForwardVideo();


public:
	UPROPERTY(EditAnywhere, Category = VideoSettings)
		class UMediaSoundComponent* soundComp;
};
