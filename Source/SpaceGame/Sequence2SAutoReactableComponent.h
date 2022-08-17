// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseReactableComponent.h"
#include "LevelSequenceActor.h"
#include "BaseInstigatorComponent.h"
#include "BaseInteractableComponent.h"
#include "Sequence2SAutoReactableComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class SPACEGAME_API USequence2SAutoReactableComponent : public UBaseReactableComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	USequence2SAutoReactableComponent();

protected:
	virtual void BeginPlay() override;

	UMovieSceneSequencePlayer* ReactionPlayer;

	bool AlteredState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interact)
	FString StageOne;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interact)
	FString StageTwo;

public:
	virtual void TriggerReaction(UBaseInstigatorComponent* instigator, UBaseInteractableComponent* interactable) override;
	virtual FString GetDescription() override;
};
