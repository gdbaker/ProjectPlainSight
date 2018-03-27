// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Player/PlainSightPlayerState.h"
#include "PlainSightGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAINSIGHT_API APlainSightGameMode : public AGameMode
{
	GENERATED_BODY()
	
	virtual void PreInitializeComponents() override;

	/** always pick new random spawn */
	virtual bool ShouldSpawnAtStartSpot(AController* Player) override;

	/** update remaining time */
	virtual void DefaultTimer();


public:
	APlainSightGameMode();
	
	/** select best spawn point for player */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/** notify about kills */
	virtual void Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType);

protected:

	/** Handle for efficient management of DefaultTimer timer */
	FTimerHandle TimerHandle_DefaultTimer;
};
