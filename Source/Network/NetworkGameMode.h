// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "NetworkGameMode.generated.h"

UCLASS(minimalapi)
class ANetworkGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	// Maximum Number of Players needed/allowed during this Match
	int32 MaxNumPlayers;

	TArray<APlayerController*> PlayerControllerList;

	// Override the PostLogin function
	virtual void PostLogin(APlayerController* NewPlayer) override;

	bool ReadyToStartMatch_Implementation() override;

	AActor* ChoosePlayerStart_Implementation(AController* Player)override;

	bool ShouldSpawnAtStartSpot(AController* Player)override{return false;};

	virtual void StartMatch() override;

	ANetworkGameMode();
};



