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

APlainSightPlayerState* APlainSightGameState::GetLeader()
{

	int32 BestPlayer = -1;
	float BestScore = -1;
	int32 BestDeaths = 9999;

	for (int32 i = 0; i < PlayerArray.Num(); i++)
	{
		const float PlayerScore = PlayerArray[i]->Score;
		if (BestScore <= PlayerScore)
		{
			APlainSightPlayerState* TempLeader = Cast<APlainSightPlayerState>(PlayerArray[i]);
			if (TempLeader->NumDeaths < BestDeaths) {
				BestScore = PlayerScore;
				BestPlayer = i;
				BestDeaths = TempLeader->NumDeaths;
			}
		}
	}

	APlainSightPlayerState* Leader = Cast<APlainSightPlayerState>(PlayerArray[BestPlayer]);

	return Leader;
}

APlainSightPlayerState* APlainSightGameState::GetSecondPlace()
{
	int32 BestPlayer = -1;
	int32 SecondPlayer = -1;
	float BestScore = -1;
	float SecondScore = -1;

	for (int32 i = 0; i < PlayerArray.Num(); i++)
	{
		const float PlayerScore = PlayerArray[i]->Score;
		if (BestScore < PlayerScore)
		{
			BestScore = PlayerScore;
			BestPlayer = i;
		}
		else if (SecondScore < PlayerScore)
		{
			SecondScore = PlayerScore;
			SecondPlayer = i;
		}
	}

	if (SecondScore == -1) {
		SecondPlayer = BestPlayer;
	}

	APlainSightPlayerState* Leader = Cast<APlainSightPlayerState>(PlayerArray[SecondPlayer]);
	return Leader;

}