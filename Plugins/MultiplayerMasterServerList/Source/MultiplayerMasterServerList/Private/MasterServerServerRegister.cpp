// Multiplayer Master Server Plugin Copyright (C) 2020 MeoPlay <contact@meoplay.com> All Rights Reserved.


#include "MasterServerServerRegister.h"
#include "Net/UnrealNetwork.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Common/UdpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/GameSession.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include <string>

#include "GenericPlatform/GenericPlatformProcess.h"

// Sets default values
AMasterServerServerRegister::AMasterServerServerRegister()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AMasterServerServerRegister::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MyServerHeartbeatTickInterval);

}


void AMasterServerServerRegister::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//~~~~~~~~~~~~~~~~

	if (SenderSocket)
	{
		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
	}
}

void AMasterServerServerRegister::UpdatePlayerCount(int newPlayerCount)
{
	MyServerCurrentNumberPlayers = newPlayerCount;
}

void AMasterServerServerRegister::UpdateMapName(FString newMapName)
{
	MyServerMapName = newMapName;
}

void AMasterServerServerRegister::UpdateMaxPlayerCount(int newMaxPlayerCount)
{
	MyServerMaxPlayers = newMaxPlayerCount;
}


// Called every frame
void AMasterServerServerRegister::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TSharedPtr<FInternetAddr>	RemoteAddr;

	int32 BytesSent = 0;
	int32 osAllocatedbuffersize = 0;

	RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool bIsValid;
	const TCHAR *TheIP = *MasterServerIp;
	RemoteAddr->SetIp(TheIP, bIsValid);
	RemoteAddr->SetPort(MasterServerPort_Register);

	if (!bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("fail register create socket!"));		
		return;
	}

	SenderSocket = FUdpSocketBuilder(TEXT("socketsendtoserver"))
		.AsNonBlocking();

	SenderSocket->SetSendBufferSize(sizeof(int), osAllocatedbuffersize);

	FString numPlayerString = FString::FromInt(MyServerCurrentNumberPlayers);
	FString numMaxPlayerString = FString::FromInt(MyServerMaxPlayers);
	FString strServerPort = FString::FromInt(GetWorld()->URL.Port);

	int UDPpacketSize = 1024;
	char *ansiiData = (char*) malloc(sizeof(char) * UDPpacketSize); 
	memset(ansiiData, '\0', UDPpacketSize);
	std::string cstr;	
	cstr.append(TCHAR_TO_ANSI(*MyServerName));
	cstr.append(TCHAR_TO_ANSI(*UDPPacketDelimiter));
	cstr.append(TCHAR_TO_ANSI(*strServerPort));
	cstr.append(TCHAR_TO_ANSI(*UDPPacketDelimiter));
	cstr.append(TCHAR_TO_ANSI(*numPlayerString));
	cstr.append(TCHAR_TO_ANSI(*UDPPacketDelimiter));
	cstr.append(TCHAR_TO_ANSI(*numMaxPlayerString));
	cstr.append(TCHAR_TO_ANSI(*UDPPacketDelimiter));
	cstr.append(TCHAR_TO_ANSI(*MyServerMapName));
	cstr.append(TCHAR_TO_ANSI(*UDPPacketDelimiter));

	strcpy(ansiiData, cstr.c_str());

	UE_LOG(LogTemp, Display, TEXT("Sending heartbeat to master server %s"), ANSI_TO_TCHAR(ansiiData));

	// send
	SenderSocket->SendTo((uint8*)ansiiData, UDPpacketSize, BytesSent, *RemoteAddr);
	free(ansiiData);
	if (BytesSent <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Socket is valid but the receiver received 0 bytes, make sure it is listening properly!"));
		return;
	}
}

