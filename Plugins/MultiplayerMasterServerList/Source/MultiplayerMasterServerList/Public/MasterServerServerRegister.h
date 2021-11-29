// Multiplayer Master Server Plugin Copyright (C) 2020 MeoPlay <contact@meoplay.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "MasterServerServerRegister.generated.h"

UCLASS()
class AMasterServerServerRegister : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterServerServerRegister();
	FSocket* SenderSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat", Meta = (ExposeOnSpawn = "true"), Meta = (ToolTip = "My server name"))
	FString MyServerName = "Default Name Server Plugin";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat", Meta = (ExposeOnSpawn = "true"), Meta = (ToolTip = "Master Server IP address"))
	FString  MasterServerIp = "192.168.1.1";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat", Meta = (ExposeOnSpawn = "true"), Meta = (ToolTip = "Master Server port Register"))
	int MasterServerPort_Register = 9993;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat")
	float MyServerHeartbeatTickInterval = 10.0f;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat", Meta = (ExposeOnSpawn = "true"), Meta = (ToolTip = "My server maximum players"))
	int MyServerMaxPlayers = 32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat", Meta = (ExposeOnSpawn = "true"), Meta = (ToolTip = "My server current number of players"))
	int MyServerCurrentNumberPlayers = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat", Meta = (ExposeOnSpawn = "true"), Meta = (ToolTip = "My server current map name"))
		FString MyServerMapName = "Map name";


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeartBeat")
	FString UDPPacketDelimiter = "*UE4PLMS*";
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "MasterServer")
	void UpdatePlayerCount(int newPlayerCount);
	UFUNCTION(BlueprintCallable, Category = "MasterServer")
	void UpdateMapName(FString newMapName);
	UFUNCTION(BlueprintCallable, Category = "MasterServer")
	void UpdateMaxPlayerCount(int newMaxPlayerCount);
};
