// Fill out your copyright notice in the Description page of Project Settings.
#include "PlainSightGameModeBase.h"
#include "PlainSight.h"
#include "ConstructorHelpers.h"



APlainSightGameModeBase::APlainSightGameModeBase()
{
	//DefaultPawnClass = APlayer_FirstPerson::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprints/Pawns/Mesh_Player.Mesh_Player_C'"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}
