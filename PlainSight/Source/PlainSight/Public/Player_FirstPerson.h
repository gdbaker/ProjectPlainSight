// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
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

	/** check if pawn is still alive */
	bool IsAlive() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//player dies
	virtual void OnDeath();

	//void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
		void Normal_Forward_Backward(float InInput);
	UFUNCTION()
		void Normal_Left_Right(float InInput);
	UFUNCTION()
		void Normal_Turn(float InInput);
	UFUNCTION()
		void LookUpDown(float InInput);
	//sets jump flag when key is pressed


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Pawn suicide */
	virtual void Suicide();

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* FirstPersonMesh;

	UFUNCTION()
		void OnStartJump();
	//clears jump flag when key is released
	UFUNCTION()
		void OnStopJump();

	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Health)
	float Health;
};
