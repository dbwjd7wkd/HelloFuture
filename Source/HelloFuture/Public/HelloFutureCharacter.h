// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Minsu_Activate.h"
#include "Minsu_PlantSeed.h"
#include "YJ_SaveGame.h" // save game
#include "Kismet/GameplayStatics.h" // save game
#include "Minsu_ShakeTree.h"
#include "Engine/SkeletalMesh.h"
#include "Materials/MaterialInterface.h"
#include "HelloFutureCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSaveGameDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadGameDelegate);
//DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerInputDelegate, class UInputComponent*)

//USTRUCT(Atomic, BlueprintType)
//struct FcloseBoughtMStruct
//{
//	GENERATED_BODY()
//	public:
//		// 구매한 옷 순서대로 in 옷장(Material array)-내부 배열
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
//			TArray<UMaterialInterface*> closetBoughtMaterial;
//};

UCLASS(config = Game)
class AHelloFutureCharacter : public ACharacter, public IMinsu_Activate, public IMinsu_PlantSeed, public IMinsu_ShakeTree
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

	/** save game**/
public:
	UFUNCTION(BlueprintCallable)
	void InitializeGame();
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame();

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

public:
	// Widget
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	//class UUserWidget* UI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI, Instanced)
	TMap<TSubclassOf<class AActor>, class UUserWidget*> WidgetMap;

	// save Game
	UPROPERTY(BlueprintReadOnly)
	class UYJ_SaveGame* SaveGameInstance;
	UPROPERTY(BlueprintReadOnly)
	class UYJ_GameInstance* gameInstance;
	UPROPERTY(BlueprintReadOnly)
	class UYJ_SaveGame* LoadGameInstance;

	// 퀘스트
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FSaveGameDelegate OnSaveGame;
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FLoadGameDelegate OnLoadGame;

	// 인벤토리시스템
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UYJ_InventoryComponent* Inventory;

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
		float time;

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

	
	//////////// 채팅 ////////////////////////////
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
		/////////////////////////////////////////////////////////////////////

	//////////// 농장 꾸미기 ////////////////////////////////////////
			
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
			int SeedCPP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
			int AmountOfWheatSeedCPP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
			int AmountOfPumpkinSeedCPP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
			int AmountOfWheatCPP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
			int AmountOfCornSeedCPP;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
			int AmountOfPumpkinCPP;



	////////////// 인터페이스 사용 //////////////////////
// public:
// 	void KeySeed();
// 	void KeyActivate();
	public:
		void KeyShakeTree();
		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Farm)
			void ShakeTree();
		virtual void ShakeTree_Implementation() override;
// 
// 	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Farm)
// 		void Activate();
// 	virtual void Activate_Implementation() override;
// 
// 	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Farm)
// 		void PlantSeed();
// 	virtual void PlantSeed_Implementation() override;

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
// 		TScriptInterface<IMinsu_Activate> minsuActive;
// 
// 	// 라인트레이스 거리
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
float TraceDistance = 500.f;

// 	// 씨앗 종류 조절
// 	void UpSeed();
// 	void DownSeed();

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Farm)
// 		int Seed = 0;
// 
// 	UPROPERTY(EditAnywhere, Category = Farm)
// 		int AmountWheatSeed = 0;
// 	UPROPERTY(EditAnywhere, Category = Farm)
// 		int AmountCornSeed = 0;
// 	UPROPERTY(EditAnywhere, Category = Farm)
// 		int AmountBushSeed = 0;
// 
// 	UPROPERTY(EditAnywhere, Category = Farm)
// 		int AmountWheat = 0;
// 	UPROPERTY(EditAnywhere, Category = Farm)
// 		int AmountCorn = 0;
// 	UPROPERTY(EditAnywhere, Category = Farm)
// 		int AmountBush = 0;

	/////////////////////////////////////////////////////////////
// 옷 구매
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoughtClothes)
		TMap<FString, bool> BoughtClothes;

	UFUNCTION(BlueprintCallable, Category = BoughtClothes)
		bool GetBoughtClothes(FString key);

	UFUNCTION(BlueprintCallable, Category = BoughtClothes)
		void SetBoughtClothes(FString key, bool value);

// 이전 맵 이름 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PreLevelName")
		FName preLevelName;

	//// 구매한 옷 순서대로 in 옷장(Mesh array)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
	//	TArray<USkeletalMesh*> closetBoughtMesh;

	//// 구매한 옷 순서대로 in 옷장(Material array)-외부 배열
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
	//	TArray<FcloseBoughtMStruct> closetBoughtMaterialStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClosetBought")
		TArray<FcloseBoughtMStruct> closetBoughts;
};

