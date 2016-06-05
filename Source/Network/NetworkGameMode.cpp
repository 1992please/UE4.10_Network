// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Network.h"
#include "NetworkGameMode.h"
#include "NetworkHUD.h"
#include "NetworkCharacter.h"
#include "NetworkPlayerController.h"
#include "MyPlayerState.h"
#include "MyPlayerStart.h"

ANetworkGameMode::ANetworkGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerControllerClass = ANetworkPlayerController::StaticClass();

	PlayerStateClass = AMyPlayerState::StaticClass();

	// use our custom HUD class
	HUDClass = ANetworkHUD::StaticClass();

	// TODO remove thid condition in release
	MaxNumPlayers = 2;
}

bool ANetworkGameMode::ReadyToStartMatch_Implementation()
{
	Super::ReadyToEndMatch_Implementation();

	return MaxNumPlayers == NumPlayers;
}

void ANetworkGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (NewPlayer)
	{
		PlayerControllerList.Add(NewPlayer);
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, "NewPlayer Joined");

		AMyPlayerState* PS = Cast<AMyPlayerState>(NewPlayer->PlayerState);

		if (PS && GameState)
		{
			uint8 NumTeamB = 0;
			uint8 NumTeamA = 0;
			for (APlayerState* It : GameState->PlayerArray)
			{
				AMyPlayerState* OtherPS = Cast<AMyPlayerState>(It);
				if (OtherPS)
				{
					if (OtherPS->bTeamB)
					{
						NumTeamB++;
					}
					else
					{
						NumTeamA++;
					}
				}
			}

			if (NumTeamA > NumTeamB)
			{
				PS->bTeamB = true;
			}
		}
	}

}

AActor* ANetworkGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (Player)
	{
		AMyPlayerState *PS = Cast<AMyPlayerState>(Player->PlayerState);
		if (PS)
		{
			TArray<AMyPlayerStart*> Starts;
			for (TActorIterator<AMyPlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
			{
				if (StartItr->bTeamB == PS->bTeamB)
				{
					Starts.Add(*StartItr);
				}
			}
			return Starts[FMath::FRandRange(0, Starts.Num() - 1)];
		}
	}
	return NULL;
}

void ANetworkGameMode::BeginPlay()
{
	Super::BeginPlay();

	const int32 tempNum = FCString::Atoi(*(UGameplayStatics::ParseOption(OptionsString, "MaxNumPlayers")));
	// TODO remove this condition in release
	if (tempNum > 0)
	{
		MaxNumPlayers = tempNum;
	}
}

void ANetworkGameMode::StartMatch()
{
	Super::StartMatch();

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, "Match Starts");

}