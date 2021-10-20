// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ_ATM.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "HelloFutureCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "YJ_InventoryComponent.h"

// Sets default values
AYJ_ATM::AYJ_ATM()
{
	//UYJ_Item* item = CreateDefaultSubobject<UYJ_Item>(TEXT("Item"));
	//AHelloFutureCharacter* myCharacter = Cast<AHelloFutureCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//myCharacter->Inventory->AddItem();
	//UYJ_Item* MyObject = NewObject<UYJ_Item>(UYJ_Item::StaticClass());

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전
	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(collision);
	collision->InitBoxExtent(FVector(120.f, 120.f, 70.f));

	// 메시
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	mesh->SetupAttachment(collision);
	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMeshAsset.Succeeded())
	{
		mesh->SetStaticMesh(CubeMeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> CubeMaterialAsset(TEXT("Material'/Engine/EditorMaterials/WidgetMaterial_Y.WidgetMaterial_Y'"));
	if (CubeMaterialAsset.Succeeded())
	{
		mesh->SetMaterial(0, CubeMaterialAsset.Object);
	}*/

	// UI
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidget (TEXT("WidgetBlueprint'/Game/YJ/UI/ATM/WBP_ATM'"));
	if (MainMenuWidget.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidget.Class;
	}
}

// Called when the game starts or when spawned
void AYJ_ATM::BeginPlay()
{
	Super::BeginPlay();
	
	isAvailable = true;

	// overlap 바인딩
	collision->OnComponentBeginOverlap.AddDynamic(this, &AYJ_ATM::OnOverlapBegin);
	collision->OnComponentEndOverlap.AddDynamic(this, &AYJ_ATM::OnOverlapEnd);
}

// Called every frame
void AYJ_ATM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AYJ_ATM::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Good"));
	player = Cast<AHelloFutureCharacter>(OtherActor);
	if (player)
	{ 
		// ATM기기를 한명 씩 사용가능하므로 현재 사용가능하다면
		if (isAvailable == true)
		{
			isAvailable = false;
			
			// UI 창 띄우기 (입금하기, 출금하기)
			ShowWidget();
		}
	}

}

void AYJ_ATM::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (player)
	{
		isAvailable = true;

		// UI 창 없애기 (입금하기, 출금하기)
		HideWidget();

	}

}

void AYJ_ATM::ShowWidget()
{
	// Create Widget and add it to viewport
	if (MainMenu == nullptr)
	{
		MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
	}
	if (!MainMenuWidgetClass) return;

	MainMenu->AddToViewport();

	// Get reference to player controller
	PlayerController = Cast<APlayerController>(player->GetController());
	if (!PlayerController) return;

	// Set Input Mode
	PlayerController->bShowMouseCursor = true;
}

void AYJ_ATM::HideWidget()
{
	MainMenu->RemoveFromViewport();
	PlayerController->bShowMouseCursor = true;
}

