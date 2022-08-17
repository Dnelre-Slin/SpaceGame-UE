// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceshipControllerComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
USpaceshipControllerComponent::USpaceshipControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

	// Input bindings
	ToggleLandingModeInputBinding = "ToggleLandingMode";
	ZeroDesiredSpeedInputBinding = "ZeroDesiredSpeed";
	TurnPitchInputBinding = "TurnPitch";
	TurnYawInputBinding = "TurnYaw";
	TurnRollInputBinding = "TurnRoll";
	ThrustForwardInputBinding = "ThrustForward";
	ThrustRightInputBinding = "ThrustRight";
	ThrustUpInputBinding = "ThrustUp";

}


// Called when the game starts
void USpaceshipControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	//APawn* OwnerPawn= Cast<APawn>(GetOwner());
	//if (OwnerPawn != nullptr && OwnerPawn->IsPlayerControlled())
	//{
	//	OwnerPawn->InputComponent->BindAction(ToggleLandingModeInputBinding, IE_Pressed, this, &USpaceshipControllerComponent::ToggleLandingMode);
	//	OwnerPawn->InputComponent->BindAction(ZeroDesiredSpeedInputBinding, IE_Pressed, this, &USpaceshipControllerComponent::ZeroOutDesiredSpeed);
	//	OwnerPawn->InputComponent->BindAxis(TurnPitchInputBinding, this, &USpaceshipControllerComponent::TurnPitchInput);
	//	OwnerPawn->InputComponent->BindAxis(TurnYawInputBinding, this, &USpaceshipControllerComponent::TurnYawInput);
	//	OwnerPawn->InputComponent->BindAxis(TurnRollInputBinding, this, &USpaceshipControllerComponent::TurnRollInput);
	//	OwnerPawn->InputComponent->BindAxis(ThrustForwardInputBinding, this, &USpaceshipControllerComponent::ThrustForwardInput);
	//	OwnerPawn->InputComponent->BindAxis(ThrustRightInputBinding, this, &USpaceshipControllerComponent::ThrustRightInput);
	//	OwnerPawn->InputComponent->BindAxis(ThrustUpInputBinding, this, &USpaceshipControllerComponent::ThrustUpInput);
	//}
}

void USpaceshipControllerComponent::SetupInputBindings_Implementation(UInputComponent* PlayerInputComponent)
{
	//if (PlayerInputComponent != nullptr)
	{
		PlayerInputComponent->BindAction(ToggleLandingModeInputBinding, IE_Pressed, this, &USpaceshipControllerComponent::ToggleLandingMode);
		PlayerInputComponent->BindAction(ZeroDesiredSpeedInputBinding, IE_Pressed, this, &USpaceshipControllerComponent::ZeroOutDesiredSpeed);
		PlayerInputComponent->BindAxis(TurnPitchInputBinding, this, &USpaceshipControllerComponent::TurnPitchInput);
		PlayerInputComponent->BindAxis(TurnYawInputBinding, this, &USpaceshipControllerComponent::TurnYawInput);
		PlayerInputComponent->BindAxis(TurnRollInputBinding, this, &USpaceshipControllerComponent::TurnRollInput);
		PlayerInputComponent->BindAxis(ThrustForwardInputBinding, this, &USpaceshipControllerComponent::ThrustForwardInput);
		PlayerInputComponent->BindAxis(ThrustRightInputBinding, this, &USpaceshipControllerComponent::ThrustRightInput);
		PlayerInputComponent->BindAxis(ThrustUpInputBinding, this, &USpaceshipControllerComponent::ThrustUpInput);
	}
}

void USpaceshipControllerComponent::ThrustForwardInput(float Val)
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

void USpaceshipControllerComponent::ThrustRightInput(float Val)
{
	DesiredVelocity.Y = Val * ThrustMaxSpeed.Y;
}

void USpaceshipControllerComponent::ThrustUpInput(float Val)
{
	DesiredVelocity.Z = Val * ThrustMaxSpeed.Z;
}

void USpaceshipControllerComponent::TurnPitchInput(float Val)
{
	GetOwner()->AddActorLocalRotation(FRotator(Val, 0.f, 0.f), true);
}

void USpaceshipControllerComponent::TurnYawInput(float Val)
{
	GetOwner()->AddActorLocalRotation(FRotator(0.f, Val, 0.f), true);
}

void USpaceshipControllerComponent::TurnRollInput(float Val)
{
	GetOwner()->AddActorLocalRotation(FRotator(0.f, 0.f, Val * TurningRates.Roll), true);
}

void USpaceshipControllerComponent::ToggleLandingMode()
{
	LandingModeActive = !LandingModeActive;
	LandingModeActiveHud = LandingModeActive;
}

void USpaceshipControllerComponent::ZeroOutDesiredSpeed()
{
	DesiredForwardSpeed = 0.f;
}


// Called every frame
void USpaceshipControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate change in CurrentVelocity
	FVector acceleration = DeltaTime * ThrustAcceleration;

	FVector delta = DesiredVelocity - CurrentVelocity;
	delta.X = FMath::Clamp(delta.X, -acceleration.X, acceleration.X);
	delta.Y = FMath::Clamp(delta.Y, -acceleration.Y, acceleration.Y);
	delta.Z = FMath::Clamp(delta.Z, -acceleration.Z, acceleration.Z);
	CurrentVelocity += delta;

	// Move plan forwards (with sweep so we stop when we collide with things)
	struct FHitResult* outhit = nullptr;
	GetOwner()->AddActorLocalOffset(CurrentVelocity * DeltaTime, true, outhit);
	//UE_LOG(LogTemp, Log, TEXT("Ticking along..."))
	if (outhit != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("After this:"))
		UE_LOG(LogTemp, Log, TEXT("%s"), *(outhit->GetActor()->GetName()))
		UE_LOG(LogTemp, Log, TEXT("Before this:"))
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("SADKLFJSD:"))
	}

	CurrentForwardSpeedHud = UKismetMathLibrary::NormalizeToRange(CurrentVelocity.X, -ThrustMaxSpeed.X, ThrustMaxSpeed.X);
	DesiredForwardSpeedHud = UKismetMathLibrary::NormalizeToRange(DesiredForwardSpeed, -ThrustMaxSpeed.X, ThrustMaxSpeed.X);
}

