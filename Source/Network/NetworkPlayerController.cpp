// Fill out your copyright notice in the Description page of Project Settings.

#include "Network.h"
#include "NetworkPlayerController.h"



void ANetworkPlayerController::OnKilled()
{
	UnPossess();
	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &ANetworkPlayerController::Respawn, 5.f);
}

void ANetworkPlayerController::Respawn()
{
	AGameMode* GameMode = GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		APawn* NewPawn = GameMode->SpawnDefaultPawnFor(this, GameMode->ChoosePlayerStart(this));
		Possess(NewPawn);
	}
}
