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

/*AActor * APlainSightGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	
}*/
