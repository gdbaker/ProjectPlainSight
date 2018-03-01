// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "TakeHitInfo.h"
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

	/** spawn inventory, setup initial variables */
	virtual void PostInitializeComponents() override;

	// Constructor for AFPSCharacter
	APlayer_FirstPerson(const FObjectInitializer& ObjectInitializer);
	
	/** get max health */
	int32 GetMaxHealth() const;

	/** check if pawn is still alive */
	bool IsAlive() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	/** notification when killed, for both the server and client. */
	virtual void OnDeath(float KillingDamage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser);

	/** sets up the replication for taking a hit */
	void ReplicateHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser, bool bKilled);

	/** play hit or death on client */
	UFUNCTION()
	void OnRep_LastTakeHitInfo();

	//void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	/** switch to ragdoll */
	void SetRagdollPhysics();

	UFUNCTION()
		void Normal_Forward_Backward(float InInput);
	UFUNCTION()
		void Normal_Left_Right(float InInput);
	UFUNCTION()
		void Normal_Turn(float InInput);
	UFUNCTION()
		void LookUpDown(float InInput);
	//sets jump flag when key is pressed

	/** Replicate where this pawn was last hit and damaged */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_LastTakeHitInfo)
	struct FTakeHitInfo LastTakeHitInfo;

	/** Time at which point the last take hit info for the actor times out and won't be replicated; Used to stop join-in-progress effects all over the screen */
	float LastTakeHitTimeTimeout;

	//traces weapon
	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace);

	UFUNCTION(reliable, NetMultiCast, WithValidation)
	virtual void GoVisible();

	UFUNCTION(reliable, NetMultiCast, WithValidation)
	virtual void GoInvisible();

	/* Handle to manage the timer */
	FTimerHandle InvisibilityTimerHandle;

	/** Responsible for cleaning up bodies on clients. */
	virtual void TornOff();

public:	

	/**
	* Kills pawn.  Server/authority only.
	* @param KillingDamage - Damage amount of the killing blow
	* @param DamageEvent - Damage event of the killing blow
	* @param Killer - Who killed this pawn
	* @param DamageCauser - the Actor that directly caused the damage (i.e. the Projectile that exploded, the Weapon that fired, etc)
	* @returns true if allowed
	*/
	virtual bool Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

	/** Returns True if the pawn can die in the current state */
	virtual bool CanDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser) const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Take damage, handle death */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	/** Pawn suicide */
	virtual void Suicide();

	/** Called on the actor right before replication occurs */
	virtual void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker) override;

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

	/** Identifies if pawn is in its dying state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	uint32 bIsDying : 1;

	UFUNCTION(reliable, server, WithValidation)
	void Attack(const FVector& StartTrace, const FVector& EndTrace);

	UFUNCTION(reliable, server, WithValidation)
	void InvisibleAttack();
};
