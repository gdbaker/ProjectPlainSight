// Fill out your copyright notice in the Description page of Project Settings.
#include "PlainSightGameModeBase.h"
#include "PlainSight.h"

#include "Player_FirstPerson.h"


APlainSightGameModeBase::APlainSightGameModeBase()
{
	DefaultPawnClass = APlayer_FirstPerson::StaticClass();
}
