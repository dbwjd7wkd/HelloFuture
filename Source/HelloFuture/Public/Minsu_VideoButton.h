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

	//������ �������̵� - >>UUserWidget - virtual Ű���� ã��
	//NativeConstruct == �����ڰ� ����÷���
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Play;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Back;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Forward;
	//-> meta  : ������ ��ư ����� ����. ��ȿ�� �˻� ���ص� �ȴ�.

private:
	// ��ư�� ���ε��� �Լ� -> �׻� UFUNCTION
	UFUNCTION()
		void MediaPlay();

	UFUNCTION()
		void MediaBack();

	UFUNCTION()
		void MediaForward();

public:
	class AMinsu_Video* videoActor;
};
