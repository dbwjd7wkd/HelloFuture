// Fill out your copyright notice in the Description page of Project Settings.


#include "Minsu_VideoButton.h"
#include "Components/Button.h"
#include "Minsu_Video.h"

void UMinsu_VideoButton::NativeConstruct()
{
	Super::NativeConstruct();

	//// 버튼 이벤트 콜백 바인딩하기
	//btn_Play->OnClicked.AddDynamic(this, &UMinsu_VideoButton::MediaPlay);
	//btn_Back->OnClicked.AddDynamic(this, &UMinsu_VideoButton::MediaBack);
	//btn_Forward->OnClicked.AddDynamic(this, &UMinsu_VideoButton::MediaForward);

}

void UMinsu_VideoButton::MediaPlay()
{
	/*if (videoActor)
	{
		videoActor->PlayVideo(UMediaSource* playSource);
	}*/

}

void UMinsu_VideoButton::MediaBack()
{
	/*if (videoActor)
	{
		videoActor->BackVideo();
	}*/
}

void UMinsu_VideoButton::MediaForward()
{
	/*if (videoActor)
	{
		videoActor->ForwardVideo();
	}*/
}