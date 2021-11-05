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
	//	// �̵�� �÷��̾ ���������� ����
	//	if (mediaPlayer->IsPlaying())
	//	{
	//		mediaPlayer->Close();
	//	}
	//	// �׷��� ������ �ҽ� ������ ����
	//	else
	//	{
	//		//UE_LOG(LogTemp, Warning, TEXT("VideoPlaying!!"));
	//		mediaPlayer->OpenSource(mysource);	// ���� ������ ��⿡ �ȴ� ��
	//	}

	//}

	if (mediaPlayer)
	{
		mediaPlayer->OpenSource(playSource);
	}


}

void AMinsu_Video::BackVideo()
{
	// ����, �̵� �÷��� ���̶��, ���� �ð� -5�� �κ��� �÷����Ѵ�
	if (mediaPlayer)
	{
		if (mediaPlayer->IsPlaying())
		{
			// Timespan�� ��� �� ����, �ð��� �޾ƿͼ� 5�� ���� �÷���
			FTimespan playTime = mediaPlayer->GetTime() - FTimespan(0, 0, 5);
			mediaPlayer->Seek(playTime);
			mediaPlayer->Play();
		}
	}
}

void AMinsu_Video::ForwardVideo()
{
	// ����, �̵� �÷��� ���̶��, ���� �ð� +5�� �κ��� �÷����Ѵ�
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

