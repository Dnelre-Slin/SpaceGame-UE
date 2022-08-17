// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceshipPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpaceshipPawn::ASpaceshipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Meshes/BasicBox.BasicBox"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());	// Set static mesh
	RootComponent = PlaneMesh;
	
	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);	// Attach SpringArm to RootComponent
	SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = false;	// Do not allow camera to lag
	SpringArm->CameraLagSpeed = 15.f;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);	// Attach the camera
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	CurrentVelocity = FVector(0.f, 0.f, 0.f);
	DesiredVelocity = FVector(0.f, 0.f, 0.f);

	// Default thrusts
	ThrustAcceleration.X = 500.f;
	ThrustAcceleration.Y = 500.f;
	ThrustAcceleration.Z = 500.f;

	ThrustMaxSpeed.X = 4000.f;
	ThrustMaxSpeed.Y = 4000.f;
	ThrustMaxSpeed.Z = 4000.f;

	DesiredForwardSpeed = 0.0f;
	DesiredForwardSpeedRateOfChange = 2000.f;

	// Turning rates
	TurningRates.Pitch = 0.1;
	TurningRates.Yaw = 0.1;
	TurningRates.Roll = 0.5;

	LandingModeActive = false;

	// Hud
	LandingModeActiveHud = false;
	CurrentForwardSpeedHud = 0.5f;
	DesiredForwardSpeedHud = 0.5f;

	FpsCharacterPawn = nullptr;
}

void ASpaceshipPawn::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Deflect along the surface when we collide.
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}

// Called when the game starts or when spawned
void ASpaceshipPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceshipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Calculate change in CurrentVelocity
	FVector acceleration = DeltaTime * ThrustAcceleration;

	FVector delta = DesiredVelocity - CurrentVelocity;
	delta.X = FMath::Clamp(delta.X, -acceleration.X, acceleration.X);
	delta.Y = FMath::Clamp(delta.Y, -acceleration.Y, acceleration.Y);
	delta.Z = FMath::Clamp(delta.Z, -acceleration.Z, acceleration.Z);
	CurrentVelocity += delta;

	// Move plan forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(CurrentVelocity * DeltaTime, true);

	CurrentForwardSpeedHud = UKismetMathLibrary::NormalizeToRange(CurrentVelocity.X, -ThrustMaxSpeed.X, ThrustMaxSpeed.X);
	DesiredForwardSpeedHud = UKismetMathLibrary::NormalizeToRange(DesiredForwardSpeed, -ThrustMaxSpeed.X, ThrustMaxSpeed.X);
}

void ASpaceshipPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UE_LOG(LogTemp, Log, TEXT("SpaceShipPossessed!"))
}

void ASpaceshipPawn::UnPossessed()
{
	Super::UnPossessed();
	UE_LOG(LogTemp, Log, TEXT("UnPossesed spaceship"))
}

// Called to bind functionality to input
void ASpaceshipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Actions
	PlayerInputComponent->BindAction("ToggleLandingMode", IE_Pressed, this, &ASpaceshipPawn::ToggleLandingMode);
	PlayerInputComponent->BindAction("ZeroDesiredSpeed", IE_Pressed, this, &ASpaceshipPawn::ZeroOutDesiredSpeed);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASpaceshipPawn::SwapPawn);
	
	// Axis
	PlayerInputComponent->BindAxis("TurnPitch", this, &ASpaceshipPawn::TurnPitchInput);
	PlayerInputComponent->BindAxis("TurnYaw", this, &ASpaceshipPawn::TurnYawInput);
	PlayerInputComponent->BindAxis("TurnRoll", this, &ASpaceshipPawn::TurnRollInput);

	PlayerInputComponent->BindAxis("ThrustForward", this, &ASpaceshipPawn::ThrustForwardInput);
	PlayerInputComponent->BindAxis("ThrustRight", this, &ASpaceshipPawn::ThrustRightInput);
	PlayerInputComponent->BindAxis("ThrustUp", this, &ASpaceshipPawn::ThrustUpInput);

}

void ASpaceshipPawn::ThrustForwardInput(float Val)
{
	if (LandingModeActive)
	{
		DesiredVelocity.X = Val * ThrustMaxSpeed.X;
	}
	else
	{
		DesiredForwardSpeed += Val * DesiredForwardSpeedRateOfChange * GetWorld()->GetDeltaSeconds();
		DesiredVelocity.X = DesiredForwardSpeed;
	}
}

void ASpaceshipPawn::ThrustRightInput(float Val)
{
	DesiredVelocity.Y = Val * ThrustMaxSpeed.Y;
}

void ASpaceshipPawn::ThrustUpInput(float Val)
{
	DesiredVelocity.Z = Val * ThrustMaxSpeed.Z;
}

void ASpaceshipPawn::TurnPitchInput(float Val)
{
	AddActorLocalRotation(FRotator(Val, 0.f, 0.f));
}

void ASpaceshipPawn::TurnYawInput(float Val)
{
	AddActorLocalRotation(FRotator(0.f, Val, 0.f));
}

void ASpaceshipPawn::TurnRollInput(float Val)
{
	AddActorLocalRotation(FRotator(0.f, 0.f, Val * TurningRates.Roll));
}

void ASpaceshipPawn::ToggleLandingMode()
{
	LandingModeActive = !LandingModeActive;
	LandingModeActiveHud = LandingModeActive;
}

void ASpaceshipPawn::ZeroOutDesiredSpeed()
{
	DesiredForwardSpeed = 0.f;
}

void ASpaceshipPawn::SwapPawn()
{
	if (FpsCharacterPawn != nullptr)
	{
		GetController()->Possess(FpsCharacterPawn);
	}
}

