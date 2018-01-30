// Fill out your copyright notice in the Description page of Project Settings.

#include "PlainSightGameMode.h"
#include "PlainSight.h"
#include "ConstructorHelpers.h"

APlainSightGameMode::APlainSightGameMode()
{
	//DefaultPawnClass = APlayer_FirstPerson::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprints/Pawns/Mesh_Player'"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}