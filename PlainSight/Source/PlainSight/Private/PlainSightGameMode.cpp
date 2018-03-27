// Fill out your copyright notice in the Description page of Project Settings.

#include "PlainSightGameMode.h"
#include "PlainSight.h"
#include "Player/PlainSightPlayerController.h"
#include "Player/PlainSightPlayerState.h"
#include "PlainSightGameState.h"
#include "ConstructorHelpers.h"

APlainSightGameMode::APlainSightGameMode()
{
	//DefaultPawnClass = APlayer_FirstPerson::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprints/Pawns/Mesh_Player.Mesh_Player_C'"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
	PlayerControllerClass = APlainSightPlayerController::StaticClass();
	PlayerStateClass = APlainSightPlayerState::StaticClass();
	GameStateClass = APlainSightGameState::StaticClass();
}

AActor * APlainSightGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	return Super::ChoosePlayerStart_Implementation(Player);
}

bool APlainSightGameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}

void APlainSightGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	GetWorldTimerManager().SetTimer(TimerHandle_DefaultTimer, this, &APlainSightGameMode::DefaultTimer, GetWorldSettings()->GetEffectiveTimeDilation(), true);
}

void APlainSightGameMode::DefaultTimer()
{

	APlainSightGameState* const MyGameState = Cast<APlainSightGameState>(GameState);
	if (MyGameState && MyGameState->RemainingTime > 0)
	{
		MyGameState->RemainingTime--;

		if (MyGameState->RemainingTime <= 0)
		{
			if (GetMatchState() == MatchState::WaitingPostMatch)
			{
				RestartGame();
			}
			else if (GetMatchState() == MatchState::InProgress)
			{
				//FinishMatch();
				EndMatch();

				// Send end round events
				/*for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
				{
					APlainSightPlayerController* PlayerController = Cast<APlainSightPlayerController>(*It);

					if (PlayerController && MyGameState)
					{
						APlainSightGameState* PlayerState = Cast<APlainSightGameState>((*It)->PlayerState);
						const bool bIsWinner = IsWinner(PlayerState);

						PlayerController->ClientSendRoundEndEvent(bIsWinner, MyGameState->ElapsedTime);
					}
				}*/
			}
			else if (GetMatchState() == MatchState::WaitingToStart)
			{
				StartMatch();
			}
		}
	}
}

void APlainSightGameMode::Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType)
{
	APlainSightPlayerState* KillerPlayerState = Killer ? Cast<APlainSightPlayerState>(Killer->PlayerState) : NULL;
	APlainSightPlayerState* VictimPlayerState = KilledPlayer ? Cast<APlainSightPlayerState>(KilledPlayer->PlayerState) : NULL;
	int32 KillScore = 1;
	int32 DeathScore = 1;

	if (KillerPlayerState && KillerPlayerState != VictimPlayerState)
	{
		KillerPlayerState->ScoreKill(VictimPlayerState, KillScore);
		//KillerPlayerState->InformAboutKill(KillerPlayerState, DamageType, VictimPlayerState);
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->ScoreDeath(KillerPlayerState, DeathScore);
		//VictimPlayerState->BroadcastDeath(KillerPlayerState, DamageType, VictimPlayerState);
	}
}