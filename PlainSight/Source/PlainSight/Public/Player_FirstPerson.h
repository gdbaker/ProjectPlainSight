// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Player_FirstPerson.generated.h"


UCLASS()
class PLAINSIGHT_API APlayer_FirstPerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_FirstPerson();
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FirstPersonCameraComponent;

	// Constructor for AFPSCharacter
	APlayer_FirstPerson(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void Normal_Forward_Backward(float InInput);
	UFUNCTION()
		void Normal_Left_Right(float InInput);
	UFUNCTION()
		void Normal_Turn(float InInput);
	UFUNCTION()
		void LookUpDown(float InInput);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
