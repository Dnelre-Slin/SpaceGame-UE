// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretActor.generated.h"

UCLASS()
class SPACEGAME_API ATurretActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// virtual void AimAtTarget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category="Aiming")
	void AimAtTarget(float deltaSeconds, USceneComponent* turretStandComp, USceneComponent* turretTopComp);

	UPROPERTY(EditAnywhere)
	AActor* targetActor;

	UPROPERTY(EditAnywhere)
	float baseTurnSpeed;
	UPROPERTY(EditAnywhere)
	float barrelTurnSpeed;
	UPROPERTY(EditAnywhere)
	float baseMinAngle;
	UPROPERTY(EditAnywhere)
	float baseMaxAngle;
	UPROPERTY(EditAnywhere)
	float barrelMinAngle;
	UPROPERTY(EditAnywhere)
	float barrelMaxAngle;

};
