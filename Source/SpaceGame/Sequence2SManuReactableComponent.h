// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sequence2SAutoReactableComponent.h"
#include "ActorSequenceComponent.h"
#include "Sequence2SManuReactableComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class SPACEGAME_API USequence2SManuReactableComponent : public USequence2SAutoReactableComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USequence2SManuReactableComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Sequence)
	UActorSequenceComponent* Sequence;

public:
	UFUNCTION(BlueprintCallable)
	void SetSequence(UActorSequenceComponent* NewSequence) { Sequence = NewSequence; }
};
