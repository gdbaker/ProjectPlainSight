// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlainSightPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PLAINSIGHT_API APlainSightPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	/** respawn after dying */
	virtual void UnFreeze() override;
	
};
