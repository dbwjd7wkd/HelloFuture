// Multiplayer Master Server Plugin Copyright (C) 2020 MeoPlay <contact@meoplay.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
//Networking
#include "Networking.h"
#include "Common/UdpSocketReceiver.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "MasterServerClientGetList.generated.h"


#if PLATFORM_IOS
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#endif



DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FDelegateReceivedServerData, FString, ServerIP, int, ServerPort, FString, ServerName,  int, CurrentPlayerCount, int, MaxPlayerCount, FString, ServerMapName);

UCLASS()
class AMasterServerClientGetList : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterServerClientGetList();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterServer", Meta = (ExposeOnSpawn = "true"), Meta = (ToolTip = "Master Server IP address"))
	FString  MasterServerIp = "192.168.1.1";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MasterServer", Meta = (ExposeOnSpawn = "true"), Meta = (ToolTip = "Master Server port GetList"))
	int MasterServerIpPort_GetList = 9994;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Test")
		FDelegateReceivedServerData OnDelegateReceivedServerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat")
		FString UDPPacketDelimiter = "*UE4PLMS*";

private:
	FSocket* SenderSocket;
	FSocket* ListenSocket;
	FUdpSocketReceiver* UDPReceiver = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category= "MasterServer")
	void AskServersList();

};
