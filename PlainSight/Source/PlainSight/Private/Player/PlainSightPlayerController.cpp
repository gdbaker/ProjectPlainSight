// Fill out your copyright notice in the Description page of Project Settings.

#include "PlainSightPlayerController.h"
#include "Player_FirstPerson.h"
#include "PlainSight.h"
#include "Player/PlainSightPlayerState.h"



void APlainSightPlayerController::UnFreeze()
{
	ServerRestartPlayer();
}


void APlainSightPlayerController::Suicide()
{
	if (IsInState(NAME_Playing))
	{
		ServerSuicide();
	}
}

bool APlainSightPlayerController::ServerSuicide_Validate()
{
	return true;
}

void APlainSightPlayerController::ServerSuicide_Implementation()
{
	if ((GetPawn() != NULL) && ((GetWorld()->TimeSeconds - GetPawn()->CreationTime > 1) || (GetNetMode() == NM_Standalone)))
	{
		APlayer_FirstPerson* MyPawn = Cast<APlayer_FirstPerson>(GetPawn());
		if (MyPawn)
		{
			MyPawn->Suicide();
		}
	}
}