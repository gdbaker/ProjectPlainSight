// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlainSightPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PLAINSIGHT_API APlainSightPlayerState : public APlayerState
{
	GENERATED_BODY()
	APlainSightPlayerState(const FObjectInitializer& ObjectInitializer);

public:
	/** Identifies if pawn is in its dying state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	uint32  IsAttacking : 1;
	
protected:
	/** number of kills */
	UPROPERTY(Transient, Replicated)
	int32 NumKills;

	/** number of deaths */
	UPROPERTY(Transient, Replicated)
	int32 NumDeaths;

	/** whether the user quit the match */
	UPROPERTY()
	uint8 bQuitter : 1;

};
