// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_Video.h"
#include "Components/SceneComponent.h"
#include "MediaPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "MediaSoundComponent.h"
#include "Components/WidgetComponent.h"
#include "Minsu_VideoButton.h"

// Sets default values
AMinsu_Video::AMinsu_Video()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	screenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen Mesh"));
	screenMesh->SetupAttachment(rootComp);

	soundComp = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Media Sound"));
	soundComp->SetupAttachment(rootComp);

	/*buttonWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Button Widget"));
	buttonWidgetComp->SetupAttachment(rootComp);*/

}

void AMinsu_Video::PlayVideo(UMediaSource* playSource)
{
	//if (mediaPlayer)
	//{
	//	// 미디어 플레이어가 열려있으면 종료
	//	if (mediaPlayer->IsPlaying())
	//	{
	//		mediaPlayer->Close();
	//	}
	//	// 그렇지 않으면 소스 파일을 연다
	//	else
	//	{
	//		//UE_LOG(LogTemp, Warning, TEXT("VideoPlaying!!"));
	//		mediaPlayer->OpenSource(mysource);	// 비디오 테이프 기기에 꽂는 것
	//	}

	//}

	if (mediaPlayer)
	{
		mediaPlayer->OpenSource(playSource);
	}


}

void AMinsu_Video::BackVideo()
{
	// 만일, 미디어가 플레이 중이라면, 현재 시간 -5초 부분을 플레이한다
	if (mediaPlayer)
	{
		if (mediaPlayer->IsPlaying())
		{
			// Timespan은 모든 언어에 있음, 시간을 받아와서 5초 전을 플레이
			FTimespan playTime = mediaPlayer->GetTime() - FTimespan(0, 0, 5);
			mediaPlayer->Seek(playTime);
			mediaPlayer->Play();
		}
	}
}

void AMinsu_Video::ForwardVideo()
{
	// 만일, 미디어가 플레이 중이라면, 현재 시간 +5초 부분을 플레이한다
	if (mediaPlayer)
	{
		if (mediaPlayer->IsPlaying())
		{
			FTimespan playTime = mediaPlayer->GetTime() + FTimespan(0, 0, 5);
			mediaPlayer->Seek(playTime);
			mediaPlayer->Play();
		}
	}
}


// Called when the game starts or when spawned
void AMinsu_Video::BeginPlay()
{
	////PlayVideo(source);
	//UMinsu_VideoButton* btnWidget = Cast<UMinsu_VideoButton>(buttonWidgetComp->GetUserWidgetObject());

	//if (btnWidget)
	//{
	//	btnWidget->videoActor = this;
	//}

	PlayVideo(source);
}

// Called every frame
void AMinsu_Video::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

