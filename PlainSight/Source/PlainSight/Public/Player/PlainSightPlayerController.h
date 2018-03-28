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

public:
	/** Causes the player to commit suicide */
	UFUNCTION(exec, BlueprintCallable, Category = "Suicide")
	virtual void Suicide();

	UFUNCTION(exec, BlueprintCallable, Category = "Invisible")
	virtual void MakeInvisible();
	
	/** Notifies the server that the client has suicided */
	UFUNCTION(reliable, server, WithValidation)
	void ServerSuicide();

	UFUNCTION(exec, BlueprintCallable, Category = "Attack")
	virtual void CallAttack(const FVector& StartTrace, const FVector& EndTrace);

	UFUNCTION(exec, BlueprintCallable, Category = "Texture")
		virtual void CallMud();
};
