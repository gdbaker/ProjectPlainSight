// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "EMPDamageType.generated.h"

/**
 * 
 */
UCLASS()
class PLAINSIGHT_API UEMPDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:

	/** True if this damagetype is caused by the world (falling off level, into lava, etc). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DamageType)
	uint32 bEMPBurst : 1;
	
	
};
