// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "NetworkPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ANetworkPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	FTimerHandle TimerHandle_Respawn;

public:

	void OnKilled();

	void Respawn();
};
