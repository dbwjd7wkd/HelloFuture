﻿// Copyright Epic Games, Inc. All Rights Reserved.

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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// 인벤토리 시스템
	Inventory = CreateDefaultSubobject<UYJ_InventoryComponent>(TEXT("Inventory"));

// 	저축왕 
// 		sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Comp"));
// 		sceneComp->SetupAttachment(RootComponent);
// 	
// 		springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
// 		springArm->SetupAttachment(sceneComp);
// 	
// 		JCKing = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("JCKing"));
// 		JCKing->SetupAttachment(springArm);

	Health = 100.f;


	/*ohController = CreateDefaultSubobject<AOH_PlayerController>(TEXT("OH_PlayerController"));*/

	// 채팅 시스템
	ChatText = CreateDefaultSubobject<UTextRenderComponent>("ChatText");
	ChatText->SetRelativeLocation(FVector(0, 0, 100));
	ChatText->SetHorizontalAlignment(EHTA_Center);
	ChatText->SetupAttachment(RootComponent);
	

}

void AHelloFutureCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentMessage = "";

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


// <<<<<<< HEAD
// // 	게시판 상호작용
// // 		PlayerInputComponent->BindAction("InteractBoard", IE_Pressed, this, &AHelloFutureCharacter::InteractBoard);
// =======
// 	// 게시판 상호작용
// 	//PlayerInputComponent->BindAction("InteractBoard", IE_Pressed, this, &AHelloFutureCharacter::InteractBoard);
// >>>>>>> afa7f2c5c76e763b45e92371270dd7ed4ced38fe
}

// void AHelloFutureCharacter::InteractBoard()
// {
// 	FHitResult OutHit;
// 	FVector Start = GetCameraBoom()->GetComponentLocation();
// 	FVector End = Start + GetCameraBoom()->GetForwardVector() * 10;
// 
// 	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility))
// 	{
// 		AMinsu_Quiz* obj = Cast<AMinsu_Quiz>(OutHit.Actor);
// 		if (obj)
// 		{
// 			obj->Interact();
// 		}
// 	}
// }

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

