// Fill out your copyright notice in the Description page of Project Settings.


#include "Sequence2SAutoReactableComponent.h"

USequence2SAutoReactableComponent::USequence2SAutoReactableComponent()
{
	AlteredState = false;

	StageOne = "Interact";
	StageTwo = "Interact";

	ReactionPlayer = nullptr;
}

// Called when the game starts
void USequence2SAutoReactableComponent::BeginPlay()
{
	Super::BeginPlay();

	ALevelSequenceActor* sequenceOwner = Cast<ALevelSequenceActor>(GetOwner());
	if (sequenceOwner != nullptr)
	{
		ReactionPlayer = sequenceOwner->GetSequencePlayer();
	}
}

void USequence2SAutoReactableComponent::TriggerReaction(UBaseInstigatorComponent* instigator, UBaseInteractableComponent* interactable)
{
	UE_LOG(LogTemp, Log, TEXT("Reaction 1"));
	if (ReactionPlayer != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Reaction 2"));
		if (!AlteredState)
		{
			UE_LOG(LogTemp, Log, TEXT("Reaction 2 false"));
			ReactionPlayer->Play();
			AlteredState = true;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Reaction 2 true"));
			ReactionPlayer->PlayReverse();
			AlteredState = false;
		}
	}
}

FString USequence2SAutoReactableComponent::GetDescription()
{
	if (AlteredState)
	{
		return StageTwo;
	}
	else
	{
		return StageOne;
	}
}

