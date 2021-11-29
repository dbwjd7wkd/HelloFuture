// Multiplayer Master Server Plugin Copyright (C) 2020 MeoPlay <contact@meoplay.com> All Rights Reserved.

#include "MasterServerClientGetList.h"
#include "MasterServerServerRegister.h"
#include "Net/UnrealNetwork.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Common/UdpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "string.h"

AMasterServerClientGetList::AMasterServerClientGetList()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SenderSocket = NULL;
	ListenSocket = NULL;
	UDPReceiver = NULL;
}

// Called when the game starts or when spawned
void AMasterServerClientGetList::BeginPlay()
{
	Super::BeginPlay();

	
	//BUFFER SIZE
	int32 BufferSize = 2 * 1024 * 1024;
	SenderSocket = FUdpSocketBuilder(TEXT("listsocketsendtoserver"))
		.AsNonBlocking()
		.AsReusable()
		.WithReceiveBufferSize(BufferSize);
	;
	
	if (SenderSocket == NULL) {
		UE_LOG(LogTemp, Error, TEXT("NULL SOCKET SEND"));
	}

}

// Called when the game starts or when spawned
void AMasterServerClientGetList::Tick(float DeltaTime) {


	TSharedRef<FInternetAddr> targetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	TArray<uint8> ReceivedData;
	uint32 Size;

	while (SenderSocket != NULL && SenderSocket->HasPendingData(Size)) {
		
		if (Size <= 1) break;

		uint8 *Recv = new uint8[Size];
		int32 BytesRead = 0;

		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		SenderSocket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *targetAddr);
		//Do something with the received data

		char ansiiData[1024];

		memcpy(ansiiData, ReceivedData.GetData(), BytesRead); 

		ansiiData[BytesRead] = 0; 

		FString dataMasterServerPacket = ANSI_TO_TCHAR(ansiiData);
		UE_LOG(LogTemp, Display, TEXT("Data received from master server pending %d : %s"), Size, *dataMasterServerPacket);
		

		if (dataMasterServerPacket.Len() <= 1) break;

		/* parse udp packet received from master server that sent its game servers list*/
		int searchres = dataMasterServerPacket.Find(UDPPacketDelimiter);
		FString parsedIP = dataMasterServerPacket.Left(searchres);
		dataMasterServerPacket = dataMasterServerPacket.RightChop(searchres + UDPPacketDelimiter.Len());

		searchres = dataMasterServerPacket.Find(UDPPacketDelimiter);
		FString parsedServerName = dataMasterServerPacket.Left(searchres);
		dataMasterServerPacket = dataMasterServerPacket.RightChop(searchres + UDPPacketDelimiter.Len());
		

		searchres = dataMasterServerPacket.Find(UDPPacketDelimiter);
		FString strCurrentServerPort = dataMasterServerPacket.Left(searchres);
		int parsedServerPort = FCString::Atoi(*strCurrentServerPort);
		dataMasterServerPacket = dataMasterServerPacket.RightChop(searchres + UDPPacketDelimiter.Len());


		searchres = dataMasterServerPacket.Find(UDPPacketDelimiter);
		FString strCurrentPlayerCount = dataMasterServerPacket.Left(searchres);
		int parsedCurrentPlayerCount = FCString::Atoi(*strCurrentPlayerCount);
		dataMasterServerPacket = dataMasterServerPacket.RightChop(searchres + UDPPacketDelimiter.Len());
				
		searchres = dataMasterServerPacket.Find(UDPPacketDelimiter);
		FString strCurrentMaxPlayerCount = dataMasterServerPacket.Left(searchres);
		int parsedCurrentMaxPlayerCount = FCString::Atoi(*strCurrentMaxPlayerCount);
		dataMasterServerPacket = dataMasterServerPacket.RightChop(searchres + UDPPacketDelimiter.Len());
				
		FString parsedServerMapName = dataMasterServerPacket;
		dataMasterServerPacket = dataMasterServerPacket.RightChop(searchres + UDPPacketDelimiter.Len());
		
		// use a dispatcher to send game server data to whoever need it
		OnDelegateReceivedServerData.Broadcast(*parsedIP, parsedServerPort, *parsedServerName, parsedCurrentPlayerCount, parsedCurrentMaxPlayerCount, *parsedServerMapName);
		
		
	}
}


void AMasterServerClientGetList::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (SenderSocket)
	{
		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
	}

	if (ListenSocket)
	{
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
	}


	if (UDPReceiver != nullptr) {
		UDPReceiver->Stop();
		UDPReceiver->Exit();
		delete UDPReceiver;
		UDPReceiver = nullptr;
	}

}


// Use this function to request server list
void AMasterServerClientGetList::AskServersList()
{	
	UE_LOG(LogTemp, Display, TEXT("Client ask server list"));

	TSharedPtr<FInternetAddr>	RemoteAddr;
	int32 BytesSent = 0;
	int32 osAllocatedbuffersize = 0;

	RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool bIsValid;
	const TCHAR *TheIP = *MasterServerIp;
	RemoteAddr->SetIp(TheIP, bIsValid);
	RemoteAddr->SetPort(MasterServerIpPort_GetList);

	SenderSocket->SetSendBufferSize(sizeof(int), osAllocatedbuffersize);


	if (!bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("GetList fail remote addr"));		
		return;
	}


	int isAlive = 1;
	FArrayWriter Writer;
	Writer << isAlive;
	SenderSocket->SendTo(Writer.GetData(), Writer.Num(), BytesSent, *RemoteAddr);

	if (BytesSent <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("GetList Socket is valid but the receiver received 0 bytes, make sure it is listening properly!"));
		return;
	}
}

