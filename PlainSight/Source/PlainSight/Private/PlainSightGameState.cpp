// Fill out your copyright notice in the Description page of Project Settings.

#include "PlainSightGameState.h"
#include "PlainSight.h"
#include "UnrealNetwork.h"

APlainSightGameState::APlainSightGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	RemainingTime = 180;
}

void APlainSightGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlainSightGameState, RemainingTime);
}

TArray<APlainSightPlayerState*> APlainSightGameState::SortPlayersArray() {

	TArray<APlainSightPlayerState*> TempPlayerArray;

	for (int32 i = 0; i < PlayerArray.Num(); i++) {

		if (APlainSightPlayerState* TempPlayer = Cast<APlainSightPlayerState>(PlayerArray[i]))
		{
			TempPlayerArray.Add(TempPlayer);
		}
	}

	TempPlayerArray.Sort(APlainSightGameState::ConstPredicate);

	return TempPlayerArray;
}

APlainSightPlayerState* APlainSightGameState::GetLeader()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Here")));
	TArray<APlainSightPlayerState*> TempPlayerArray;

	for (int32 i = 0; i < PlayerArray.Num(); i++) {

		if (APlainSightPlayerState* TempPlayer = Cast<APlainSightPlayerState>(PlayerArray[i]))
		{
			TempPlayerArray.Add(TempPlayer);
		}
	}

	TempPlayerArray.Sort(APlainSightGameState::ConstPredicate);

	/*int32 BestPlayer = -1;
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
	}*/

	//APlainSightPlayerState* Leader = Cast<APlainSightPlayerState>(PlayerArray[BestPlayer]);

	if (TempPlayerArray.Num() > 0) {
		return TempPlayerArray[0];
	}
	else {

		return nullptr;
	}
}

APlainSightPlayerState* APlainSightGameState::GetSecondPlace()
{
	TArray<APlainSightPlayerState*> TempPlayerArray;

	for (int32 i = 0; i < PlayerArray.Num(); i++) {

		if (APlainSightPlayerState* TempPlayer = Cast<APlainSightPlayerState>(PlayerArray[i]))
		{
			TempPlayerArray.Add(TempPlayer);
		}
	}

	TempPlayerArray.Sort(APlainSightGameState::ConstPredicate);
	/*int32 BestPlayer = -1;
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

	APlainSightPlayerState* Leader = Cast<APlainSightPlayerState>(PlayerArray[SecondPlayer]);*/

	if (TempPlayerArray.Num() > 1) {
		return TempPlayerArray[1];
	}
	else {
		return TempPlayerArray[0];
	}

}