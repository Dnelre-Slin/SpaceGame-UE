// Fill out your copyright notice in the Description page of Project Settings.


#include "Single2SInteractableComponent.h"

USingle2SInteractableComponent::USingle2SInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Description = "Interact";

	ActorWithReactable = nullptr;
	Reactable = nullptr;
}

void USingle2SInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ActorWithReactable != nullptr)
	{
		TArray<UBaseReactableComponent*> ReactableComps;
		ActorWithReactable->GetComponents(ReactableComps);
		if (ReactableComps.Num() > 0)
		{
			Reactable = ReactableComps[0];
		}
	}
}

FString USingle2SInteractableComponent::GetDescription()
{
	if (Reactable != nullptr)
	{
		return Reactable->GetDescription();
	}
	return Description;
}

void USingle2SInteractableComponent::OnInteract(UBaseInstigatorComponent* instigator)
{
	UE_LOG(LogTemp, Log, TEXT("OnInteract1"))
	if (Reactable != nullptr)
	{
	UE_LOG(LogTemp, Log, TEXT("OnInteract2"))
		Reactable->TriggerReaction(instigator, this);
	}
}
