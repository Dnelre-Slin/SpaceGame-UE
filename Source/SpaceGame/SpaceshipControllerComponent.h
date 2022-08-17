// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputBindingComponentInterface.h"
#include "SpaceshipControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEGAME_API USpaceshipControllerComponent : public UActorComponent, public IInputBindingComponentInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceshipControllerComponent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputBindings")
	void SetupInputBindings(UInputComponent* PlayerInputComponent);  // This is the prototype declared in the interface
	virtual void SetupInputBindings_Implementation(UInputComponent* PlayerInputComponent) override; // This is the declaration of the implementation

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Begin input bound methods
	/** Bound to forward/backward thrust W/S */
	void ThrustForwardInput(float Val);

	/** Bound to right/left thrust D/A */
	void ThrustRightInput(float Val);

	/** Bound to up/down thrust [space]/[ctrl]/[c] */
	void ThrustUpInput(float Val);

	/** Bound to vertical mouse axis */
	void TurnPitchInput(float Val);

	/** Bound to horizontal mouse axis */
	void TurnYawInput(float Val);

	/** Bound to 'E', 'Q' roll */
	void TurnRollInput(float Val);

	/** Toggle landing mode */
	void ToggleLandingMode();

	/** Zero out desired speed */
	void ZeroOutDesiredSpeed();
	// End input bound methods

	// Begin HUD variables
	/** Current forward speed clamped for hud*/
	UPROPERTY(Category = Hud, BlueprintReadOnly)
	float CurrentForwardSpeedHud;

	/** Desired forward speed clamped for hud*/
	UPROPERTY(Category = Hud, BlueprintReadOnly)
	float DesiredForwardSpeedHud;

	/** Landing mode bool for hud*/
	UPROPERTY(Category = Hud, BlueprintReadOnly)
	bool LandingModeActiveHud;
	// End HUD variables


	/** Acceleration in the different thrust directions */
	UPROPERTY(Category = Thrust, EditAnywhere)
	FVector ThrustAcceleration;

	/** Acceleration in the different thrust directions */
	UPROPERTY(Category = Thrust, EditAnywhere)
	FVector ThrustMaxSpeed;

	/** How quickly turning can happen */
	UPROPERTY(Category = Turning, EditAnywhere)
	FRotator TurningRates;

	/** Rate of change for desired forward speed */
	UPROPERTY(Category = Thrust, EditAnywhere)
	float DesiredForwardSpeedRateOfChange;

	// Input bindings:

	/** Input for ToggleLandingMode */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName ToggleLandingModeInputBinding;
	
	/** Input for ZeroDesiredSpeed */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName ZeroDesiredSpeedInputBinding;
		
	/** Input for TurnPitch */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName TurnPitchInputBinding;
		
	/** Input for TurnYaw */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName TurnYawInputBinding;
		
	/** Input for TurnYaw */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName TurnRollInputBinding;
		
	/** Input for ThrustForward */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName ThrustForwardInputBinding;
			
	/** Input for ThrustRight */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName ThrustRightInputBinding;
			
	/** Input for ThrustUp */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName ThrustUpInputBinding;

	// Input bindings end

	/** Current velocity vector */
	FVector CurrentVelocity;

	/** Desired velocity vector */
	FVector DesiredVelocity;

	/** Desired forward speed, in normal flight mode */
	float DesiredForwardSpeed;

	/** Whether landing mode is active or not (not means normal flight mode) */
	bool LandingModeActive;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
