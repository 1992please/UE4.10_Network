// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "NetworkHUD.generated.h"

UCLASS()
class ANetworkHUD : public AHUD
{
	GENERATED_BODY()

public:
	ANetworkHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

