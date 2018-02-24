// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_FirstPerson.h"
#include "Components/CapsuleComponent.h" 

#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

// Sets default values
APlayer_FirstPerson::APlayer_FirstPerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayer_FirstPerson::BeginPlay()
{
	Super::BeginPlay();
	//GetMesh()->SetOwnerNoSee(true);
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
	// everyone but the owner can see the regular body mesh
	//GetMesh()->SetOwnerNoSee(true);
}

