// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HelloFutureCharacter.generated.h"


//DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerInputDelegate, class UInputComponent*)

UCLASS(config=Game)
class AHelloFutureCharacter : public ACharacter
{
	GENERATED_BODY()


		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

public:
	AHelloFutureCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;




protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/*void InteractBoard();*/

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// 인벤토리시스템
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UYJ_InventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
		float Health;

	UFUNCTION(BlueprintCallable, Category = "Items")
		void UseItem(class UYJ_Item* Item);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EPressed")
		bool isEPressed;


	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	class AOH_PlayerController* ohController;*/

// 
// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
//  	class AOH_PlayerController* ohController;



// 	UPROPERTY(VisibleAnywhere, Category = "SceneCapture2D")
// 		class USceneComponent* sceneComp;
// 	UPROPERTY(VisibleAnywhere, Category = "SceneCapture2D")
// 		class USpringArmComponent* springArm;
// 	UPROPERTY(VisibleAnywhere, Category = "SceneCapture2D")
// 		class USceneCaptureComponent2D* JCKing;


//FPlayerInputDelegate OninputDelegate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
		FText Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Name)
		class UMinsu_NameInputUserWidget* nameWidget;

	UFUNCTION(BlueprintCallable, Category = Name)
		void CreatePlayerHUD(FText playerName);

	UPROPERTY(EditDefaultsOnly, Category = Name)
		TSubclassOf<UUserWidget> nameWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quiz)
		int32 quizScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quiz)
		bool isQuiz = false;


	///////////// Interactive //////////////////

protected :
	class AOH_InteractiveBase* currentInteractive;

public:
	FORCEINLINE class AOH_InteractiveBase* GetInteractive() {return currentInteractive; }

	void SetInteractiveInRange(class AOH_InteractiveBase* Interactive);
	void ClearInteractiveInRange(class AOH_InteractiveBase* Interactive);


	//////////// 채팅 ///////////////
public:
	void Chatting();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chat)
			class UTextRenderComponent* ChatText;

		virtual void BeginPlay() override;

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

		UFUNCTION(BlueprintCallable, Category = Chat)
			void AttemptToSendChatMessage(const FString& Message);

		// 채팅 보내기 (서버에 있을때만 실행 가능), 서버에 없다면 ServerSendChatMessage 실행
		UFUNCTION(BlueprintCallable, Category = Chat)
			void SendChatMessage(const FString& Message);

		// 현재 메세지 지우기 (채팅 보내고 5초 후)
		UFUNCTION(BlueprintCallable, Category = Chat)
			void ClearChatMessage();

		UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = Chat)
			void ServerSendChatMessage(const FString& Message);
		void ServerSendChatMessage_Implementation(const FString& Message);
		bool ServerSendChatMessage_Validate(const FString& Message);

		UFUNCTION(BlueprintCallable, Category = Chat)
			void OnRep_CurrentMessage();

		UFUNCTION(BlueprintCallable, Category = Chat)
			void UpdateChatText();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, ReplicatedUsing = OnRep_CurrentMessage, Category = Chat)
			FString CurrentMessage;
	
		UPROPERTY(EditDefaultsOnly, Category = Chat)
			TSubclassOf<UUserWidget> ChatWidgetClass;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Chat)
			class UMinsu_ChatWidget* ChatWidget;

	//////////// 농장 꾸미기 ///////////////

	// 농작물 활성화 O키
	void PlantSeed();

	// 농작물 씨앗뿌리기 P키
	void PlantActivate();

	// 라인트레이스 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
	float TraceDistance = 2000.f;

	// 씨앗 개수 조절
	void UpSeed();
	void DownSeed();

	UPROPERTY(EditAnywhere, Category = Farm)
		int32 Seed = 0;

	UPROPERTY(EditAnywhere, Category = Farm)
		int32 AmountWheatSeed = 0;
	UPROPERTY(EditAnywhere, Category = Farm)
		int32 AmountCornSeed = 0;
	UPROPERTY(EditAnywhere, Category = Farm)
		int32 AmountBushSeed = 0;

	UPROPERTY(EditAnywhere, Category = Farm)
		int32 AmountWheat = 0;
	UPROPERTY(EditAnywhere, Category = Farm)
		int32 AmountCorn = 0;
	UPROPERTY(EditAnywhere, Category = Farm)
		int32 AmountBush = 0;
};

