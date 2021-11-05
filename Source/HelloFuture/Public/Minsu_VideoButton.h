// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Minsu_VideoButton.generated.h"

/**
 * 
 */
UCLASS()
class HELLOFUTURE_API UMinsu_VideoButton : public UUserWidget
{
	GENERATED_BODY()

public:

	//생성자 오버라이딩 - >>UUserWidget - virtual 키워드 찾기
	//NativeConstruct == 생성자겸 비긴플레이
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Play;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Back;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Forward;
	//-> meta  : 강제로 버튼 만들어 버림. 유효성 검사 안해도 된다.

private:
	// 버튼에 바인딩할 함수 -> 항상 UFUNCTION
	UFUNCTION()
		void MediaPlay();

	UFUNCTION()
		void MediaBack();

	UFUNCTION()
		void MediaForward();

public:
	class AMinsu_Video* videoActor;
};
