// Fill out your copyright notice in the Description page of Project Settings.

#include "PlainSightGameState.h"
#include "PlainSight.h"
#include "UnrealNetwork.h"

APlainSightGameState::APlainSightGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	RemainingTime = 0;
}

void APlainSightGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlainSightGameState, RemainingTime);
}

