// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelloFutureCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "YJ_Item.h"
#include "YJ_InventoryComponent.h"
#include "Minsu_Quiz.h"
#include <Components/SceneCaptureComponent2D.h>
#include <Components/SceneComponent.h>
#include "HelloFutureGameMode.h"
#include <Minsu_NameInputUserWidget.h>
#include <Internationalization/Text.h>
#include "HelloFuture.h"
#include <Logging/LogMacros.h>
#include <GameFramework/Actor.h>
#include <Blueprint/UserWidget.h>
#include "Minsu_Activate.h"
#include "Minsu_PlantSeed.h"
#include <Materials/MaterialInterface.h>
#include <Minsu_ChatWidget.h>


//////////////////////////////////////////////////////////////////////////
// AHelloFutureCharacter

AHelloFutureCharacter::AHelloFutureCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// 인벤토리 시스템
	Inventory = CreateDefaultSubobject<UYJ_InventoryComponent>(TEXT("Inventory"));

	Health = 100.f;

	// 채팅 시스템
	ChatText = CreateDefaultSubobject<UTextRenderComponent>("ChatText");
	ChatText->SetRelativeLocation(FVector(0, 0, 100));
	ChatText->SetHorizontalAlignment(EHTA_Center);
	ChatText->SetupAttachment(RootComponent);
	ChatText->SetVerticalAlignment(EVRTA_TextCenter);
	ChatText->SetTextRenderColor(FColor::Black);
	ChatText->SetText(TEXT(""));
	
	ConstructorHelpers::FObjectFinder<UMaterial> MatFinder(TEXT("Material'/Game/Minsu/Minsu_TextMat.Minsu_TextMat'"));
	if (MatFinder.Succeeded())
	{
		ChatText->SetTextMaterial(MatFinder.Object);
	}
	
	ConstructorHelpers::FObjectFinder<UFont> FontFinder(TEXT("Font'/Game/Oh/Font/OH_Font.OH_Font'"));
	if (FontFinder.Succeeded())
	{
		ChatText->SetFont(FontFinder.Object);
	}


}

void AHelloFutureCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentMessage = "";

	APlayerController* playerController = Cast<APlayerController>(GetController());
	if (playerController) {
		playerController->bShowMouseCursor = true;
		playerController->bEnableClickEvents = true;
		playerController->bEnableMouseOverEvents = true;
	}

}

void AHelloFutureCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHelloFutureCharacter, CurrentMessage);

}

void AHelloFutureCharacter::AttemptToSendChatMessage(const FString& Message)
{

	// 만약 서버가 없다면 ServersendChat message를 보내고
	// 아니라면, send chat message를 이용
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerSendChatMessage(Message);
	}
	else
	{
		SendChatMessage(Message);
	}
}

void AHelloFutureCharacter::SendChatMessage(const FString& Message)
{
	CurrentMessage = Message;
	UpdateChatText();

	FTimerHandle DummyHandle;
	GetWorldTimerManager().SetTimer(DummyHandle, this, &AHelloFutureCharacter::ClearChatMessage, 5.f);
}

void AHelloFutureCharacter::ClearChatMessage()
{
	CurrentMessage = "";
	UpdateChatText();
}

void AHelloFutureCharacter::ServerSendChatMessage_Implementation(const FString& Message)
{
	SendChatMessage(Message);
}

bool AHelloFutureCharacter::ServerSendChatMessage_Validate(const FString& Message)
{
	if (Message.Len() < 255)
	{
		return true;
	}
	else return false;
}

void AHelloFutureCharacter::OnRep_CurrentMessage()
{
	UpdateChatText();
}

void AHelloFutureCharacter::UpdateChatText()
{
	ChatText->SetText(FText::FromString(CurrentMessage));
}


//////////////////////////////////////////////////////////////////////////
// Input

void AHelloFutureCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHelloFutureCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHelloFutureCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHelloFutureCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHelloFutureCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHelloFutureCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHelloFutureCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AHelloFutureCharacter::OnResetVR);

	////////////// 채팅 ////////////////
	PlayerInputComponent->BindAction("Chatting", IE_Pressed, this, &AHelloFutureCharacter::Chatting);


	//////////// 농장 꾸미기 ///////////////
	
// 	농작물 활성화 O키
// 	PlayerInputComponent->BindAction("PlantActivate", IE_Pressed, this, &AHelloFutureCharacter::KeyActivate);
// 	
// 	// 농작물 씨앗뿌리기 P키
// 	PlayerInputComponent->BindAction("PlantSeed", IE_Pressed, this, &AHelloFutureCharacter::KeySeed);
// 
// 	// 씨앗개수 조절
// 	PlayerInputComponent->BindAction("SeedUp", IE_Pressed, this, &AHelloFutureCharacter::UpSeed);
// 	PlayerInputComponent->BindAction("SeedDown", IE_Pressed, this, &AHelloFutureCharacter::DownSeed);

}

// 인벤토리 시스템
void AHelloFutureCharacter::UseItem(class UYJ_Item* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); // bp event
	}
}


void AHelloFutureCharacter::CreatePlayerHUD(FText playerName)
{
	if (nameWidgetClass)
	{
		nameWidget = CreateWidget<UMinsu_NameInputUserWidget>(GetWorld(), nameWidgetClass);
		if (nameWidget)
		{
			nameWidget->AddToViewport();
		}
	}
}

void AHelloFutureCharacter::OnResetVR()
{
	// If HelloFuture is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in HelloFuture.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHelloFutureCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AHelloFutureCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AHelloFutureCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHelloFutureCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHelloFutureCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHelloFutureCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AHelloFutureCharacter::SetInteractiveInRange(class AOH_InteractiveBase* Interactive)
{
	if (Interactive != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WWWw"));
		currentInteractive = Interactive;
		
		
	}
}

void AHelloFutureCharacter::ClearInteractiveInRange(class AOH_InteractiveBase* Interactive)
{
	
	currentInteractive = nullptr;
	
}

void AHelloFutureCharacter::Chatting()
{
	if (ChatWidgetClass)
	{
		ChatWidget = CreateWidget<UMinsu_ChatWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ChatWidgetClass);
		if (ChatWidget)
		{
			ChatWidget->AddToViewport();
		}
	}
}

// void AHelloFutureCharacter::Activate_Implementation()
// {
// 	/*UE_LOG(LogTemp, Warning, TEXT("Activate"));*/
// }
// 
// void AHelloFutureCharacter::KeySeed()
// {
// // 	FHitResult HitResult;
// // 	FVector CamLoc;
// // 	FRotator CamRot;
// // 
// // 	GetController()->GetPlayerViewPoint(CamLoc, CamRot);
// // 
// // 	FVector StartTrace = CamLoc;
// // 	FVector EndTrace = StartTrace + (CamRot.Vector() * TraceDistance);
// // 
// // 	FCollisionQueryParams TraceParams;
// // 	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams);
// // 
// // 	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 2.0f);
// // 
// // 	if (bHit)
// // 	{
// // 		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5, 5, 5), FColor::Green, false, 2.0f);
// // 		
// // 		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UMinsu_PlantSeed::StaticClass()))
// // 		{
// // 			IMinsu_PlantSeed::Execute_PlantSeed(HitResult.GetActor());
// // 		}
// // 
// // 	}
// }
// 
// void AHelloFutureCharacter::PlantSeed_Implementation()
// {
// 	/*UE_LOG(LogTemp, Warning, TEXT("PlantSeed"));*/
// }
// 
// void AHelloFutureCharacter::KeyActivate()
// {
// // 	FHitResult HitResult;
// // 	FVector CamLoc;
// // 	FRotator CamRot;
// // 
// // 	GetController()->GetPlayerViewPoint(CamLoc, CamRot);
// // 
// // 	FVector StartTrace = CamLoc;
// // 	FVector EndTrace = StartTrace + (CamRot.Vector() * TraceDistance);
// // 
// // 	FCollisionQueryParams TraceParams;
// // 	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams);
// // 
// // 	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 2.0f);
// // 
// // 	if (bHit)
// // 	{
// // 		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5, 5, 5), FColor::Red, false, 2.0f);
// // 		
// // 		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UMinsu_Activate::StaticClass()))
// // 		{
// // 			IMinsu_Activate::Execute_Activate(HitResult.GetActor());
// // 		}
// // 	}
// 	
// }
// 
// void AHelloFutureCharacter::UpSeed()
// {
// 	/*Seed = FMath::Clamp(Seed + 1, 0, 2);*/
// }
// 
// void AHelloFutureCharacter::DownSeed()
// {
// 	/*Seed = FMath::Clamp(Seed - 1, 0, 2);*/
// }

