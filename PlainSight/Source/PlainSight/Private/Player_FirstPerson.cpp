// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_FirstPerson.h"
#include "PlainSightGameMode.h"
#include "PlainSight.h"
#include "Player/PlainSightPlayerState.h"
#include "Components/CapsuleComponent.h" 
#include "UnrealNetwork.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

// Sets default values
APlayer_FirstPerson::APlayer_FirstPerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
void APlayer_FirstPerson::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (Role == ROLE_Authority)
	{
		Health = GetMaxHealth();
	}

}
// Called when the game starts or when spawned
void APlayer_FirstPerson::BeginPlay()
{
	Super::BeginPlay();
	//GetMesh()->SetOwnerNoSee(true);
}
void APlayer_FirstPerson::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);

	// Only replicate this property for a short duration after it changes so join in progress players don't get spammed with fx when joining late
	DOREPLIFETIME_ACTIVE_OVERRIDE(APlayer_FirstPerson, LastTakeHitInfo, GetWorld() && GetWorld()->GetTimeSeconds() < LastTakeHitTimeTimeout);
}

void APlayer_FirstPerson::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(APlayer_FirstPerson, LastTakeHitInfo, COND_Custom);

	// Replicate to everyone
	DOREPLIFETIME(APlayer_FirstPerson, Health);
}

int32 APlayer_FirstPerson::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<APlayer_FirstPerson>()->Health;
}

bool APlayer_FirstPerson::Attack_Validate(const FVector& StartTrace, const FVector& EndTrace)
{
	return true;
}


void APlayer_FirstPerson::Attack_Implementation(const FVector& StartTrace, const FVector& EndTrace)
{
	FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	if (Impact.bBlockingHit && (Impact.GetActor() != NULL))
	{
		FPointDamageEvent PointDmg;
		PointDmg.HitInfo = Impact;
		//PointDmg.ShotDirection = ShootDir;

		//change this to a variable at some point for damage
		PointDmg.Damage = 100.0f;
		Impact.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, this->Controller, this);
	}

}

FHitResult APlayer_FirstPerson::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace)
{

	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("BLADE_TRACE")), true, this);
	TraceParams.AddIgnoredActor(this);
	TraceParams.bTraceComplex = true;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_BLADE, TraceParams);

	return Hit;
}
bool APlayer_FirstPerson::InvisibleAttack_Validate()
{
	return true;
}


void APlayer_FirstPerson::InvisibleAttack_Implementation()
{
	//UGameplayStatics::ApplyRadialDamage(this, WeaponConfig.ExplosionDamage, NudgedImpactLocation, WeaponConfig.ExplosionRadius, WeaponConfig.DamageType, TArray<AActor*>(), this, MyController.Get());


}

float APlayer_FirstPerson::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{

	if (Health <= 0.f)
	{
		return 0.f;
	}

	if (this && EventInstigator)
	{
		APlainSightPlayerState* DamagedPlayerState = Cast<APlainSightPlayerState>(this->PlayerState);
		APlainSightPlayerState* InstigatorPlayerState = Cast<APlainSightPlayerState>(EventInstigator->PlayerState);

		//dont kill self
		if (InstigatorPlayerState == DamagedPlayerState)
		{
			Damage = 0.f;
		}
	}

	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		if (Health <= 0)
		{
			Die(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			//PlayHit(ActualDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		}
	}

	return ActualDamage;
}

bool APlayer_FirstPerson::CanDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser) const
{
	if (bIsDying										// already dying
		|| IsPendingKill()								// already destroyed
		|| Role != ROLE_Authority						// not authority
		|| GetWorld()->GetAuthGameMode<APlainSightGameMode>() == NULL
		|| GetWorld()->GetAuthGameMode<APlainSightGameMode>()->GetMatchState() == MatchState::LeavingMap)	// level transition occurring
	{
		return false;
	}

	return true;
}

bool APlayer_FirstPerson::Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser) {
	if (!CanDie(KillingDamage, DamageEvent, Killer, DamageCauser))
	{
		return false;
	}

	OnDeath(KillingDamage, DamageEvent, Killer ? Killer->GetPawn():NULL, DamageCauser);

	return true;
}

void APlayer_FirstPerson::OnDeath(float KillingDamage, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser){
	if (bIsDying)
	{
		return;
	}

	//bReplicateMovement = false;
	bTearOff = true;
	bIsDying = true;

	if (Role == ROLE_Authority)
	{
		ReplicateHit(KillingDamage, DamageEvent, PawnInstigator, DamageCauser, true);
	}

	DetachFromControllerPendingDestroy();

	//instead of destroy could add death animation
	//Destroy();

	if (GetMesh())
	{
		static FName CollisionProfileName(TEXT("Ragdoll"));
		GetMesh()->SetCollisionProfileName(CollisionProfileName);
	}
	SetActorEnableCollision(true);

	// Ragdoll
	SetRagdollPhysics();

	// disable collisions on capsule
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

}

void APlayer_FirstPerson::SetRagdollPhysics()
{
	bool bInRagdoll = false;

	if (IsPendingKill())
	{
		bInRagdoll = false;
	}
	else if (!GetMesh() || !GetMesh()->GetPhysicsAsset())
	{
		bInRagdoll = false;
	}
	else
	{
		// initialize physics/etc
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetMesh()->bBlendPhysics = true;

		bInRagdoll = true;
	}

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->SetComponentTickEnabled(false);

	if (!bInRagdoll)
	{
		// hide and set short lifespan
		TurnOff();
		SetActorHiddenInGame(true);
		SetLifeSpan(10.0f);
	}
	else
	{
		SetLifeSpan(10.0f);
	}
}

void APlayer_FirstPerson::ReplicateHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser, bool bKilled)
{
	const float TimeoutTime = GetWorld()->GetTimeSeconds() + 0.5f;

	FDamageEvent const& LastDamageEvent = LastTakeHitInfo.GetDamageEvent();
	if ((PawnInstigator == LastTakeHitInfo.PawnInstigator.Get()) && (LastDamageEvent.DamageTypeClass == LastTakeHitInfo.DamageTypeClass) && (LastTakeHitTimeTimeout == TimeoutTime))
	{
		// same frame damage
		if (bKilled && LastTakeHitInfo.bKilled)
		{
			// Redundant death take hit, just ignore it
			return;
		}

		// otherwise, accumulate damage done this frame
		Damage += LastTakeHitInfo.ActualDamage;
	}

	LastTakeHitInfo.ActualDamage = Damage;
	LastTakeHitInfo.PawnInstigator = Cast<APlayer_FirstPerson>(PawnInstigator);
	LastTakeHitInfo.DamageCauser = DamageCauser;
	LastTakeHitInfo.SetDamageEvent(DamageEvent);
	LastTakeHitInfo.bKilled = bKilled;
	LastTakeHitInfo.EnsureReplication();

	LastTakeHitTimeTimeout = TimeoutTime;
}

void APlayer_FirstPerson::OnRep_LastTakeHitInfo()
{
	if (LastTakeHitInfo.bKilled)
	{
		OnDeath(LastTakeHitInfo.ActualDamage, LastTakeHitInfo.GetDamageEvent(), LastTakeHitInfo.PawnInstigator.Get(), LastTakeHitInfo.DamageCauser.Get());
	}
	else
	{
		//can use play hit from shootergame here
		//PlayHit(LastTakeHitInfo.ActualDamage, LastTakeHitInfo.GetDamageEvent(), LastTakeHitInfo.PawnInstigator.Get(), LastTakeHitInfo.DamageCauser.Get());
	}
}

void APlayer_FirstPerson::Suicide() {
	if (Role == ROLE_Authority && !bIsDying)
	{
		AController* Killer = NULL;

		Die(Health, FDamageEvent(UDamageType::StaticClass()), Killer, NULL);
	}
	
}
void APlayer_FirstPerson::Normal_Forward_Backward(float InInput)
{
	FRotator Rotation = GetControlRotation();
	//to be changed later if we want to add ladders
	Rotation.Pitch = 0;
	FVector MovementDirection = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(MovementDirection, InInput);
}

void APlayer_FirstPerson::Normal_Left_Right(float InInput)
{
	FRotator Rotation = GetControlRotation();
	//to be changed later if we want to add ladders
	Rotation.Pitch = 0;
	FVector MovementDirection = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(MovementDirection, InInput);
}

void APlayer_FirstPerson::Normal_Turn(float InInput)
{
}

void APlayer_FirstPerson::LookUpDown(float InInput)
{
}
void APlayer_FirstPerson::OnStartJump()
{
	bPressedJump = true;
}
void APlayer_FirstPerson::OnStopJump()
{
	bPressedJump = false;
}

// Called every frame
void APlayer_FirstPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Health %d"), this->Health));

}

// Called to bind functionality to input
void APlayer_FirstPerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Normal_Forward_Backward", this, &APlayer_FirstPerson::Normal_Forward_Backward);
	InputComponent->BindAxis("Normal_Left_Right", this, &APlayer_FirstPerson::Normal_Left_Right);
	InputComponent->BindAxis("Turn", this, &APlayer_FirstPerson::AddControllerYawInput);
	InputComponent->BindAxis("LookUpDown", this, &APlayer_FirstPerson::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_FirstPerson::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayer_FirstPerson::OnStopJump);
}

//Constructor for mesh player

APlayer_FirstPerson::APlayer_FirstPerson(const FObjectInitializer& ObjectInitializer)
{
	// Create a CameraComponent 
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachTo((USceneComponent*)GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// Allow the pawn to control camera rotation.
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);         // only the owning player will see this mesh
	FirstPersonMesh->AttachTo(FirstPersonCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->SetCollisionResponseToChannel(COLLISION_BLADE, ECR_Ignore);
	// everyone but the owner can see the regular body mesh
	//GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_BLADE, ECR_Block);
}


bool APlayer_FirstPerson::IsAlive() const
{
	return Health > 0;
}
