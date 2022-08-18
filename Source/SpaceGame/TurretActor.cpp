// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretActor.h"
#include "Math/Quat.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATurretActor::ATurretActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->targetActor = nullptr;
	// this->turretStandComp = nullptr;
	// this->turretTopComp = nullptr;

	this->baseTurnSpeed = 6.f;
	this->barrelTurnSpeed = 6.f;
	this->baseMinAngle = -180.f;
	this->baseMaxAngle = 180.f;
	this->barrelMinAngle = -180.f;
	this->barrelMaxAngle = 30.f;

	// UE_LOG(LogTemp, Log, TEXT("WHAT"));
}

// Called when the game starts or when spawned
void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretActor::AimAtTarget(float deltaSeconds, USceneComponent* turretStandComp, USceneComponent* turretTopComp)
{
	if (this->targetActor != nullptr && turretStandComp != nullptr && turretTopComp != nullptr)
	{
		FVector vecToTarget = this->targetActor->GetActorLocation() - turretTopComp->GetComponentLocation();

		FQuat quatToTarget = FQuat::FindBetween(FVector::ForwardVector, this->GetActorQuat().Inverse() * vecToTarget);
		FVector rotations = quatToTarget.Euler();
		rotations = FVector(-rotations.X, -rotations.Y, rotations.Z);
		UE_LOG(LogTemp, Log, TEXT("Rotations: x=%f, y=%f, z=%f"), rotations.X, rotations.Y, rotations.Z);

		float zRotationClamped = FMath::Clamp(rotations.Z, this->baseMinAngle, this->baseMaxAngle);
		FQuat quatToFloorProjectedTarget = FQuat(FVector::UpVector, FMath::DegreesToRadians(zRotationClamped));

		float yRotationClamped = FMath::Clamp(rotations.Y, this->barrelMinAngle, this->barrelMaxAngle);
		FQuat quatToHeightProjectedTarget = FQuat(FVector::RightVector, FMath::DegreesToRadians(yRotationClamped));

		FQuat turretTopCompNewQuat =  turretStandComp->GetComponentQuat() * quatToHeightProjectedTarget;// * turretTopComp->GetComponentQuat();
		turretTopComp->SetWorldRotation(FQuat::Slerp(turretTopComp->GetComponentQuat(), turretTopCompNewQuat, deltaSeconds * this->barrelTurnSpeed));

		FQuat turretStandCompNewQuat = this->GetActorQuat() * quatToFloorProjectedTarget;// * turretStandComp->GetComponentQuat();
		turretStandComp->SetWorldRotation(FQuat::Slerp(turretStandComp->GetComponentQuat(), turretStandCompNewQuat, deltaSeconds * this->baseTurnSpeed));

		DrawDebugLine(this->GetWorld(), turretTopComp->GetComponentLocation(), turretTopComp->GetComponentLocation() + (turretTopComp->GetForwardVector() * 500.f), FColor::Green);
	}
}



// Called every frame
void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// this->AimAtTarget();
}

