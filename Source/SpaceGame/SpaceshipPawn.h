// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceshipPawn.generated.h"

UCLASS()
class SPACEGAME_API ASpaceshipPawn : public APawn
{
	GENERATED_BODY()

	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PlaneMesh;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

public:
	// Sets default values for this pawn's properties
	ASpaceshipPawn();

	// Begin AActor overrides
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	// End AActor overrides

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	/** Swap to fps character pawn */
	void SwapPawn();
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

private:
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

	/** Current velocity vector */
	FVector CurrentVelocity;

	/** Desired velocity vector */
	FVector DesiredVelocity;

	/** Desired forward speed, in normal flight mode */
	float DesiredForwardSpeed;

	/** Whether landing mode is active or not (not means normal flight mode) */
	bool LandingModeActive;

	/** FpsCharacterPawn */
	UPROPERTY(Category = Pawns, EditAnywhere)
	APawn* FpsCharacterPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	/** Returns PlaneMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetPlaneMesh() const { return PlaneMesh; }
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

};
