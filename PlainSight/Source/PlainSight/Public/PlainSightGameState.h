// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Player/PlainSightPlayerState.h"
#include "PlainSightGameState.generated.h"

/**
 * 
 */
UCLASS()
class PLAINSIGHT_API APlainSightGameState : public AGameState
{
	GENERATED_BODY()
	APlainSightGameState(const FObjectInitializer& ObjectInitializer);

	inline static bool ConstPredicate(const APlainSightPlayerState& ps1, const APlainSightPlayerState& ps2)
	{
		if (ps1.NumKills == ps2.NumKills) {
			return (ps1.NumDeaths < ps2.NumDeaths);
		}
		else {
			return (ps1.NumKills > ps2.NumKills);
		}
	}

public:
	/** time left for warmup / match */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Replicated)
	int32 RemainingTime;

	UFUNCTION(BlueprintCallable, Category = "Scores")
	APlainSightPlayerState* GetLeader();

	UFUNCTION(BlueprintCallable, Category = "Scores")
	TArray<APlainSightPlayerState*> SortPlayersArray();

	UFUNCTION(BlueprintCallable, Category = "Scores")
	APlainSightPlayerState* GetSecondPlace();
};
