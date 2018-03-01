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
	
public:
	/** Identifies if pawn is in its dying state */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	uint32 bIsAttacking : 1;
	
	
};
