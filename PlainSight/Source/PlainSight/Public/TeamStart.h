// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "TeamStart.generated.h"

/**
 * 
 */
UCLASS()
class PLAINSIGHT_API ATeamStart : public APlayerStart
{
	GENERATED_BODY()
	
	UPROPERTY(EditInstanceOnly, Category = Team)
	int32 SpawnTeam;
	
	
};
