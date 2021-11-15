 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OH_PlayerController.generated.h"

/**
 * 
 */

UCLASS()
class HELLOFUTURE_API AOH_PlayerController : public APlayerController
{
	GENERATED_BODY()


	/*virtual void InitializeComponent() override;*/
	
private:


	virtual void BeginPlay() override;

	/*UFUNCTION(BlueprintCallable, Category = "Input")
	void LockInput;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ULockInput;*/

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
AOH_PlayerController();

class AHelloFutureCharacter* me;

UPROPERTY(BlueprintReadWrite, Category = "Player UI")
class UOH_QuestUI* oh_QuestUI;

TSubclassOf<class UUserWidget> oh_QuestUIclass;

FORCEINLINE UOH_QuestUI* GetUI() {return Cast<UOH_QuestUI>(oh_QuestUI); };
//FORCEINLINE UOH_QuestUI* GetUI() {return  oh_QuestUI;}

void SetupInputComponent();
UPROPERTY(BlueprintReadWrite, Category = "datatable")
class UOH_DataTable* datatable;


UPROPERTY()
class AApple* apple;



public:

UFUNCTION(BlueprintCallable, Category = "Input")
void Interact();

UFUNCTION(BlueprintCallable, Category = "Input")
void OnKeyUp();

UFUNCTION(BlueprintCallable, Category = "Input")
void OnKeyDown();




protected:

UFUNCTION()
void OnintroDialogueCompleted();

//UPROPERTY(BlueprintAssignable)
//FOnActionPress OnActionPressed;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
class UDataTable* IntroDialogue;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
class UDataTable* FarmDialogue;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
class UDataTable* MainMapDialogue;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
class UDataTable* BankDialogue;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
class UDataTable* ShopDialogue;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
class UDataTable* CustomDialogue;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
class UDataTable* ClothingDialogue;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	bool isPlaying = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool isfirstFarm = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool isfirstMainMap = false;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool isfirstShop = false;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool isfirstBank = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool isfirstcustom = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool isfirstclothing = false;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool interactQuest = false;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool introtutorialfinish = false;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Tutorial1 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Tutorial2 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Tutorial3 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Tutorial4 = false;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool farmtutorial1 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool farmtutorial2 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool farmtutorial3 = false;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Towntutorial1 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Towntutorial2 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Towntutorial3 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Shoptutorial1 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Shoptutorial2 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Shoptutorial3 = false;


UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Banktutorial1 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Banktutorial2 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Banktutorial3 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Banktutorial4 = false;



UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Clothingtutorial1 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Clothingtutorial2 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Clothingtutorial3 = false;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
bool Clothingtutorial4 = false;
};
