// Fill out your copyright notice in the Description page of Project Settings.

#include "PlainSightPlayerController.h"
#include "Player_FirstPerson.h"
#include "PlainSight.h"



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

void APlainSightPlayerController::CallAttack(const FVector& StartTrace, const FVector& EndTrace)
{
	if ((GetPawn() != NULL) && ((GetWorld()->TimeSeconds - GetPawn()->CreationTime > 1) || (GetNetMode() == NM_Standalone)) && IsInState(NAME_Playing))
	{
		APlayer_FirstPerson* MyPawn = Cast<APlayer_FirstPerson>(GetPawn());
		if (MyPawn)
		{
			MyPawn->Attack(StartTrace, EndTrace);
		}
	}
}


void APlainSightPlayerController::MakeInvisible()
{
	if ((GetPawn() != NULL) && ((GetWorld()->TimeSeconds - GetPawn()->CreationTime > 1) || (GetNetMode() == NM_Standalone)) && IsInState(NAME_Playing))
	{
		APlayer_FirstPerson* MyPawn = Cast<APlayer_FirstPerson>(GetPawn());
		if (MyPawn)
		{
			MyPawn->InvisibleAttack();
		}

	}
}