// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlainSightGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAINSIGHT_API APlainSightGameMode : public AGameMode
{
	GENERATED_BODY()

	/** always pick new random spawn */
	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;

public:
	APlainSightGameMode();
	
	/** select best spawn point for player */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
