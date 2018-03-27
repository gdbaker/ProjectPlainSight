// Fill out your copyright notice in the Description page of Project Settings.

#include "PlainSightPlayerState.h"
#include "PlainSight.h"
#include "UnrealNetwork.h"

APlainSightPlayerState::APlainSightPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NumKills = 0;
	NumDeaths = 0;
	bQuitter = false;
}

void APlainSightPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlainSightPlayerState, NumKills);
	DOREPLIFETIME(APlainSightPlayerState, NumDeaths);
}