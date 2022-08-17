// Fill out your copyright notice in the Description page of Project Settings.


#include "Sequence2SManuReactableComponent.h"
#include "ActorSequencePlayer.h"

USequence2SManuReactableComponent::USequence2SManuReactableComponent()
{
	Sequence = nullptr;
}

void USequence2SManuReactableComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Setting sequence"))

	if (Sequence != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Sequence sat"))
		ReactionPlayer = Cast<UMovieSceneSequencePlayer>(Sequence->GetSequencePlayer());
		if (ReactionPlayer != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Sequence sat. (Actually worked)"))
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Sequence sat. (Did not work)"))
		}
	}
}
