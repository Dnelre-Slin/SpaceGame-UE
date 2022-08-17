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
	// FVector forward = this->GetActorForwardVector();
	// FVector forward = turretStandComp->GetForwardVector();
	// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (forward * 500.f), FColor::Orange);
	if (this->targetActor != nullptr && turretStandComp != nullptr && turretTopComp != nullptr)
	{
		// FVector vecToTarget = this->targetActor->GetActorLocation() - this->GetActorLocation();
		FVector vecToTarget = this->targetActor->GetActorLocation() - turretTopComp->GetComponentLocation();
		// vecToTarget.Normalize();
		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (vecToTarget * 500.f), FColor::Purple);
		// FQuat quatToTarget = FQuat::FindBetween(forward, vecToTarget);
		// quatToTarget = this->GetActorQuat().Inverse() * quatToTarget;
		// FQuat quatToTarget = FQuat::FindBetween(FVector::ForwardVector, turretTopComp->GetComponentQuat().Inverse() * vecToTarget);
		FQuat quatToTarget = FQuat::FindBetween(FVector::ForwardVector, this->GetActorQuat().Inverse() * vecToTarget);
		FVector rotations = quatToTarget.Euler();
		rotations = FVector(-rotations.X, -rotations.Y, rotations.Z);
		UE_LOG(LogTemp, Log, TEXT("Rotations: x=%f, y=%f, z=%f"), rotations.X, rotations.Y, rotations.Z);
		// FVector topAngles = (turretStandComp->GetComponentQuat().Inverse() * turretTopComp->GetComponentQuat()).Euler();
		// UE_LOG(LogTemp, Log, TEXT("Top: x=%f, y=%f, z=%f"), topAngles.X, topAngles.Y, topAngles.Z);
		// float twistAngle = quatToTarget.GetTwistAngle(FVector::UpVector);
		// UE_LOG(LogTemp, Log, TEXT("TwistAngle: x=%f"), FMath::RadiansToDegrees(twistAngle));
		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToTarget.RotateVector(this->GetActorUpVector()) * 500.f), FColor::Blue);
		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToTarget.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Red);
		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToTarget.RotateVector(this->GetActorRightVector()) * 500.f), FColor::Green);
		// FQuat quatToFloorProjectedTarget = FQuat(FVector::UpVector, FMath::DegreesToRadians(rotations.Z));
		float zRotationClamped = FMath::Clamp(rotations.Z, this->baseMinAngle, this->baseMaxAngle);
		FQuat quatToFloorProjectedTarget = FQuat(FVector::UpVector, FMath::DegreesToRadians(zRotationClamped));
		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToFloorProjectedTarget.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Yellow);
		// FQuat quatToHeightProjectedTarget = FQuat(FVector::RightVector, FMath::DegreesToRadians(rotations.Y));
		float yRotationClamped = FMath::Clamp(rotations.Y, this->barrelMinAngle, this->barrelMaxAngle);
		FQuat quatToHeightProjectedTarget = FQuat(FVector::RightVector, FMath::DegreesToRadians(yRotationClamped));
		// FQuat quatToHeightProjectedTarget = FQuat(this->GetActorRightVector(), FMath::DegreesToRadians(rotations.Y));
		// FVector topAngles = quatToHeightProjectedTarget.Euler();
		// UE_LOG(LogTemp, Log, TEXT("Top: x=%f, y=%f, z=%f"), topAngles.X, topAngles.Y, topAngles.Z);
		// FQuat quatToHeightProjectedTarget = FQuat::MakeFromEuler(FVector(0, -rotations.Y, 0));
		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToHeightProjectedTarget.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::White);
		// FQuat quatCombined = quatToFloorProjectedTarget * quatToHeightProjectedTarget;
		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatCombined.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Black);

		// UE_LOG(LogTemp, Log, TEXT("Having said A"));

		// FQuat turretTopCompNewQuat =  turretStandComp->GetComponentQuat() * quatToHeightProjectedTarget;// * turretTopComp->GetComponentQuat();
		FQuat turretTopCompNewQuat =  turretStandComp->GetComponentQuat() * quatToHeightProjectedTarget;// * turretTopComp->GetComponentQuat();
		turretTopComp->SetWorldRotation(FQuat::Slerp(turretTopComp->GetComponentQuat(), turretTopCompNewQuat, deltaSeconds * this->barrelTurnSpeed));

		FQuat turretStandCompNewQuat = this->GetActorQuat() * quatToFloorProjectedTarget;// * turretStandComp->GetComponentQuat();
		turretStandComp->SetWorldRotation(FQuat::Slerp(turretStandComp->GetComponentQuat(), turretStandCompNewQuat, deltaSeconds * this->baseTurnSpeed));

		DrawDebugLine(this->GetWorld(), turretTopComp->GetComponentLocation(), turretTopComp->GetComponentLocation() + (turretTopComp->GetForwardVector() * 500.f), FColor::Green);

		// if (turretStandComp != nullptr)
		// {
		// 	// UE_LOG(LogTemp, Log, TEXT("You must now say B"));
		// 	FQuat inverseRotate = this->GetActorQuat().Inverse();
		// 	// DrawDebugLine(this->GetWorld(), turretStandComp->GetComponentLocation(), turretStandComp->GetComponentLocation() + (turretStandComp->GetUpVector() * 500.f), FColor::Purple);
		// 	// DrawDebugLine(this->GetWorld(), turretStandComp->GetComponentLocation(), turretStandComp->GetComponentLocation() + (turretStandComp->GetForwardVector() * 500.f), FColor::Orange);
		// 	// DrawDebugLine(this->GetWorld(), turretStandComp->GetComponentLocation(), turretStandComp->GetComponentLocation() + (turretStandComp->GetRightVector() * 500.f), FColor::Yellow);
		// 	// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(turretStandComp->GetUpVector()) * 500.f), FColor::Blue);
		// 	// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(turretStandComp->GetForwardVector()) * 500.f), FColor::Red);
		// 	// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(turretStandComp->GetRightVector()) * 500.f), FColor::Green);
		// 	// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(turretStandComp->GetUpVector()) * 500.f), FColor::Blue);
		// 	// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(turretStandComp->GetForwardVector()) * 500.f), FColor::Red);
		// 	// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(turretStandComp->GetRightVector()) * 500.f), FColor::Green);

		// 	FQuat quatToFloorProjectedTargetTransformed = this->GetActorQuat() * quatToFloorProjectedTarget;
		// 	FQuat quatStand = turretStandComp->GetComponentQuat();
		// 	FQuat quatStandSlerped = FQuat::Slerp(quatStand, quatToFloorProjectedTargetTransformed, 0.1f);

		// 	// FQuat quatInvertedStand = inverseRotate * turretStandComp->GetComponentQuat();
		// 	// FQuat quatStandRotatedInverted = quatToFloorProjectedTarget * quatInvertedStand;
		// 	// FQuat quatStandRotatedSlerpedInverted = FQuat::Slerp(quatInvertedStand, quatStandRotatedInverted, 0.1f);
		// 	// FQuat quatStandRotatedSlerped = this->GetActorQuat() * quatStandRotatedSlerpedInverted;
		// 	// FQuat quatToFloorProjectedTargetRelative = quatRelativeBase.Inverse() * quatToFloorProjectedTarget;
		// 	// // FQuat quatToFloorProjectedTargetRelative = turretStandComp->GetRelativeRotationFromWorld(quatToFloorProjectedTarget);
		// 	// // FQuat quatRelativeBase = turretStandComp->GetRelativeRotationFromWorld(turretStandComp->GetComponentQuat());
		// 	// FQuat quatBaseDestination = quatToFloorProjectedTargetRelative * quatRelativeBase;
		// 	// // FQuat newQuatBase = FQuat::Slerp(quatRelativeBase, quatBaseDestination, 0.1f);
		// 	// // turretStandComp->SetWorldRotation(newQuatBase);

		// 	// turretStandComp->SetWorldRotation(quatStandSlerped);
		// }

		// if (this->turretTopComp != nullptr)
		// {
		// 	// UE_LOG(LogTemp, Log, TEXT("You must now say B"));
		// 	FQuat inverseRotate = this->GetActorQuat().Inverse();
		// 	DrawDebugLine(this->GetWorld(), this->turretTopComp->GetComponentLocation(), this->turretTopComp->GetComponentLocation() + (this->turretTopComp->GetUpVector() * 500.f), FColor::Purple);
		// 	DrawDebugLine(this->GetWorld(), this->turretTopComp->GetComponentLocation(), this->turretTopComp->GetComponentLocation() + (this->turretTopComp->GetForwardVector() * 500.f), FColor::Orange);
		// 	DrawDebugLine(this->GetWorld(), this->turretTopComp->GetComponentLocation(), this->turretTopComp->GetComponentLocation() + (this->turretTopComp->GetRightVector() * 500.f), FColor::Yellow);
		// 	DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorUpVector()) * 500.f), FColor::Blue);
		// 	DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Red);
		// 	DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorRightVector()) * 500.f), FColor::Green);
		// 	// FQuat quatRelativeTop = this->turretTopComp->GetRelativeRotationFromWorld(this->turretTopComp->GetComponentQuat());
		// 	// FQuat quatTopDestination = quatToHeightProjectedTarget * quatRelativeTop;
		// 	// FQuat newQuatTop = FQuat::Slerp(quatRelativeTop, quatTopDestination, 0.1f);
		// 	// DrawDebugLine(this->GetWorld(), this->turretTopComp->GetComponentLocation(), this->turretTopComp->GetComponentLocation() + (newQuatTop.RotateVector(this->turretTopComp->GetForwardVector()) * 1500.f), FColor::Purple);
		// 	// this->turretTopComp->SetRelativeRotation(newQuatTop);
		// }
	}
}

// void ATurretActor::AimAtTarget()
// {
// 	// FQuat quat = this->GetActorQuat();
// 	// quat.FindBetween
// 	FVector forward = this->GetActorForwardVector();
// 	DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (forward * 500.f), FColor::Orange);
// 	if (this->targetActor != nullptr)
// 	{
// 		FVector vecToTarget = this->targetActor->GetActorLocation() - this->GetActorLocation();
// 		vecToTarget.Normalize();
// 		DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (vecToTarget * 500.f), FColor::Purple);
// 		FQuat quatTransform = FQuat(FVector::ForwardVector,FMath::DegreesToRadians(-90));
// 		FQuat quatToTarget = FQuat::FindBetween(forward, vecToTarget);
// 		FQuat quatToTargetTransformed = quatToTarget * quatTransform;
// 		FVector rotations = quatToTargetTransformed.Euler();
// 		rotations = FVector(-rotations.X, rotations.Z, -rotations.Y);
// 		UE_LOG(LogTemp, Log, TEXT("Rotations: x=%f, y=%f, z=%f"), rotations.X, rotations.Y, rotations.Z);
// 		DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatTransform.RotateVector(this->GetActorUpVector()) * 500.f), FColor::Blue);
// 		DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatTransform.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Red);
// 		DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatTransform.RotateVector(this->GetActorRightVector()) * 500.f), FColor::Green);
// 		FQuat quatToHeightProjectedTarget = FQuat(FVector::UpVector, FMath::DegreesToRadians(rotations.Y));
// 		FQuat quatToFloorProjectedTarget = FQuat(FVector::RightVector, FMath::DegreesToRadians(rotations.Z));
// 		DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToFloorProjectedTarget.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Yellow);
// 		DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToHeightProjectedTarget.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::White);
// 		FQuat quatCombined = quatToHeightProjectedTarget * quatToFloorProjectedTarget;
// 		DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatCombined.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Black);

// 	}
// }

// void ATurretActor::AimAtTarget()
// {
// 	TInlineComponentArray<USceneComponent*> Components;
// 	this->GetComponents(Components);

// 	UE_LOG(LogTemp, Log, TEXT("Bottom. Ptr: %d"), this->turretStandComp);
// 	UE_LOG(LogTemp, Log, TEXT("Top. Ptr: %d"), this->turretTopComp);

// 	for (int i = 0; i < Components.Num(); i++)
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("I: %d. Ptr: %d"), i, Components[i]);
// 		UE_LOG(LogTemp, Log, TEXT("I: %d. Name: %s"), i, *(Components[i]->GetRelativeLocationPropertyName().ToString()));
// 	}
// 	// FQuat quat = this->GetActorQuat();
// 	// quat.FindBetween
// 	FVector forward = this->GetActorForwardVector();
// 	// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (forward * 500.f), FColor::Orange);
// 	if (this->targetActor != nullptr)
// 	{
// 		FVector vecToTarget = this->targetActor->GetActorLocation() - this->GetActorLocation();
// 		vecToTarget.Normalize();
// 		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (vecToTarget * 500.f), FColor::Purple);
// 		FQuat quatToTarget = FQuat::FindBetween(forward, vecToTarget);
// 		FVector rotations = quatToTarget.Euler();
// 		rotations = FVector(-rotations.X, -rotations.Y, rotations.Z);
// 		// UE_LOG(LogTemp, Log, TEXT("Rotations: x=%f, y=%f, z=%f"), rotations.X, rotations.Y, rotations.Z);
// 		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToTarget.RotateVector(this->GetActorUpVector()) * 500.f), FColor::Blue);
// 		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToTarget.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Red);
// 		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToTarget.RotateVector(this->GetActorRightVector()) * 500.f), FColor::Green);
// 		FQuat quatToFloorProjectedTarget = FQuat(FVector::UpVector, FMath::DegreesToRadians(rotations.Z));
// 		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToFloorProjectedTarget.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Yellow);
// 		FQuat quatToHeightProjectedTarget = FQuat(FVector::RightVector, FMath::DegreesToRadians(rotations.Y));
// 		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatToHeightProjectedTarget.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::White);
// 		FQuat quatCombined = quatToFloorProjectedTarget * quatToHeightProjectedTarget;
// 		// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (quatCombined.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Black);

// 		// UE_LOG(LogTemp, Log, TEXT("Having said A"));
		

// 		if (this->turretStandComp != nullptr)
// 		{
// 			// UE_LOG(LogTemp, Log, TEXT("You must now say B"));
// 			// FQuat inverseRotate = this->GetActorQuat().Inverse();
// 			// DrawDebugLine(this->GetWorld(), this->turretStandComp->GetComponentLocation(), this->turretStandComp->GetComponentLocation() + (this->turretStandComp->GetUpVector() * 500.f), FColor::Purple);
// 			// DrawDebugLine(this->GetWorld(), this->turretStandComp->GetComponentLocation(), this->turretStandComp->GetComponentLocation() + (this->turretStandComp->GetForwardVector() * 500.f), FColor::Orange);
// 			// DrawDebugLine(this->GetWorld(), this->turretStandComp->GetComponentLocation(), this->turretStandComp->GetComponentLocation() + (this->turretStandComp->GetRightVector() * 500.f), FColor::Yellow);
// 			// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorUpVector()) * 500.f), FColor::Blue);
// 			// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Red);
// 			// DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorRightVector()) * 500.f), FColor::Green);
// 			// // DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->turretStandComp->GetUpVector()) * 500.f), FColor::Blue);
// 			// // DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->turretStandComp->GetForwardVector()) * 500.f), FColor::Red);
// 			// // DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->turretStandComp->GetRightVector()) * 500.f), FColor::Green);

// 			// FQuat quatRelativeBase = this->turretStandComp->GetComponentQuat();
// 			// FQuat quatToFloorProjectedTargetRelative = quatRelativeBase.Inverse() * quatToFloorProjectedTarget;
// 			// // FQuat quatToFloorProjectedTargetRelative = this->turretStandComp->GetRelativeRotationFromWorld(quatToFloorProjectedTarget);
// 			// // FQuat quatRelativeBase = this->turretStandComp->GetRelativeRotationFromWorld(this->turretStandComp->GetComponentQuat());
// 			// FQuat quatBaseDestination = quatToFloorProjectedTargetRelative * quatRelativeBase;
// 			// // FQuat newQuatBase = FQuat::Slerp(quatRelativeBase, quatBaseDestination, 0.1f);
// 			// // this->turretStandComp->SetWorldRotation(newQuatBase);
// 		}

// 		if (this->turretTopComp != nullptr)
// 		{
// 			// UE_LOG(LogTemp, Log, TEXT("You must now say B"));
// 			FQuat inverseRotate = this->GetActorQuat().Inverse();
// 			DrawDebugLine(this->GetWorld(), this->turretTopComp->GetComponentLocation(), this->turretTopComp->GetComponentLocation() + (this->turretTopComp->GetUpVector() * 500.f), FColor::Purple);
// 			DrawDebugLine(this->GetWorld(), this->turretTopComp->GetComponentLocation(), this->turretTopComp->GetComponentLocation() + (this->turretTopComp->GetForwardVector() * 500.f), FColor::Orange);
// 			DrawDebugLine(this->GetWorld(), this->turretTopComp->GetComponentLocation(), this->turretTopComp->GetComponentLocation() + (this->turretTopComp->GetRightVector() * 500.f), FColor::Yellow);
// 			DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorUpVector()) * 500.f), FColor::Blue);
// 			DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorForwardVector()) * 500.f), FColor::Red);
// 			DrawDebugLine(this->GetWorld(), this->GetActorLocation(), this->GetActorLocation() + (inverseRotate.RotateVector(this->GetActorRightVector()) * 500.f), FColor::Green);
// 			// FQuat quatRelativeTop = this->turretTopComp->GetRelativeRotationFromWorld(this->turretTopComp->GetComponentQuat());
// 			// FQuat quatTopDestination = quatToHeightProjectedTarget * quatRelativeTop;
// 			// FQuat newQuatTop = FQuat::Slerp(quatRelativeTop, quatTopDestination, 0.1f);
// 			// DrawDebugLine(this->GetWorld(), this->turretTopComp->GetComponentLocation(), this->turretTopComp->GetComponentLocation() + (newQuatTop.RotateVector(this->turretTopComp->GetForwardVector()) * 1500.f), FColor::Purple);
// 			// this->turretTopComp->SetRelativeRotation(newQuatTop);
// 		}
// 	}
// }

// Called every frame
void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// this->AimAtTarget();
}

