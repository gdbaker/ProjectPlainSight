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

	/** player killed someone */
	void ScoreKill(APlainSightPlayerState* Victim, int32 Points);

	/** player died */
	void ScoreDeath(APlainSightPlayerState* KilledBy, int32 Points);
	
protected:
	/** number of kills */
	UPROPERTY(BlueprintReadOnly, Transient, Replicated, Category="Scores")
	int32 NumKills;

	/** number of deaths */
	UPROPERTY(BlueprintReadOnly, Transient, Replicated, Category = "Scores")
	int32 NumDeaths;

	/** whether the user quit the match */
	UPROPERTY()
	uint8 bQuitter : 1;

};
