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

public:
	/** time left for warmup / match */
	UPROPERTY(BlueprintReadOnly, Transient, Replicated)
	int32 RemainingTime;

	UFUNCTION(BlueprintCallable, Category = "Scores")
	APlainSightPlayerState* GetLeader();

	UFUNCTION(BlueprintCallable, Category = "Scores")
	APlainSightPlayerState* GetSecondPlace();
};
