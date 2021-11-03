// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YJ_InventoryComponent.generated.h"

// Blueprints will bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTaxUpdated);

UENUM(BlueprintType)
enum class EItemEnum : uint8
{
	Apple = 0,
	ClothingHelmet, // UMETA(DisplayName = "Option B")
	ClothingVest,
	CornItem,
	CornSeed,
	Radish,
	Bread,
	Lemon,
	Pumpkin,
	PumpkinSeed,
	WaterMelon,
	Wheat,
	WheatSeed = 12,
	RadishSeed,
	WaitingTicket,
	Fertilizer,
	Fertilizer2,
	MagicPowder,
	Tonic
};

USTRUCT(Atomic, BlueprintType)
struct FBankBookInterestStruct
{
	GENERATED_BODY()

public:
	// 통장이자
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		bool HaveBankBook = false; // 통장을 가지고 있는지

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		int32 BankBook_Interest = 0; // 통장 이자

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		int32 BankBook_PastDate = 0; // 통장 이자 준 후 지난 날짜

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
		float BankBook_Percent = 0.01; // 통장 이자율
};

USTRUCT(Atomic, BlueprintType)
struct FLoanStruct
{
	GENERATED_BODY()

public:
	// 대출
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		bool HaveBorrowedLoan = false; // 대출을 했었는지

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		bool UnpaidLoan = false; // 아직 안 갚은 대출금이 있는지

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		int32 Loan_Interest = 0; // 대출 이자

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		int32 Loan_PastDate = 0; // 대출 후 지난 날짜

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		float Loan_Percent = 0.05; // 대출 이자율

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
		int32 Loan_Value = 100000; // 원래 대출금
};

USTRUCT(Atomic, BlueprintType)
struct FTaxStruct
{
	GENERATED_BODY()

public:
	// 세금
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		bool UnpaidTax = false; // 아직 안 갚은 세금이 있는지

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		int32 Tax_Interest; // 세금 이자

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		int32 Tax_PastDate = 0; // 세금 고지 후 지난 날짜

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		float Tax_Percent; 	// 세금 비율

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
		int32 Tax_Content = 0; 	// 세금고지서 번호
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLOFUTURE_API UYJ_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UYJ_InventoryComponent();

	virtual void BeginPlay() override;
	// 아이템 관련 함수
	UFUNCTION(BlueprintCallable)
		bool AddItem(class UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool AddItem2(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		bool AddItemByNumber(EItemEnum Item, int32 num);

	UFUNCTION(BlueprintCallable)
		bool RemoveItem(class UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem2(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItemByNumber(EItemEnum Item, int32 num);

	UFUNCTION(BlueprintCallable)
		class UYJ_Item* EnumIndexToItem(EItemEnum Item);
	UFUNCTION(BlueprintCallable)
		bool CheckHaveItemAsYJ_Item(class UYJ_Item* Item);
	UFUNCTION(BlueprintCallable)
		bool CheckHaveItemAsEnum(EItemEnum Item);

	// 돈 관련 함수
	UFUNCTION(BlueprintCallable)
		bool MinusCash(int32 minusPrice);
	UFUNCTION(BlueprintCallable)
		bool PlusCash(int32 plusPrice);
	UFUNCTION(BlueprintCallable)
		bool MinusAccountBalance(int32 minusPrice);
	UFUNCTION(BlueprintCallable)
		bool PlusAccountBalance(int32 plusPrice);

	// 통장이자 관련 함수
	UFUNCTION(BlueprintCallable)
	bool Update_BankBook_Interest();

	// 대출 관련 함수
	UFUNCTION(BlueprintCallable)
	bool Update_Loan();

	UFUNCTION(BlueprintCallable)
	int32 Get_TotalLoanAmount();

	// 세금 관련 함수
	UFUNCTION(BlueprintCallable)
	bool Update_Tax();

public:
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UYJ_Item*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated	OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Tax")
	FOnTaxUpdated onTaxUpdated;

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	int32 accountBalance;

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	int32 cash;

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	FName state; // add, remove

	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	int32 columnLength;
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Inventory")
	int32 rowLength;

	// 인벤토리 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<class UYJ_Item*> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Items")
	int32 ItemCnt;

	// 통장이자
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BankBook")
	FBankBookInterestStruct BankBook;

	// 대출
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Loan")
	FLoanStruct Loan;

	// 세금
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tax")
	FTaxStruct Tax;

	//// SaveGame에 넣을 인벤토리 아이템 정보
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	//	TArray<int32> inventoryCnt; // 인벤토리의 각 아이템 갯수

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	//	TArray<int32> inventoryIdx; // 인벤토리의 각 아이템 인덱스
};
