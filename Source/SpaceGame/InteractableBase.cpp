// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

// Sets default values for this component's properties
UInteractableBase::UInteractableBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Description = "Interact";

}

// Called when the game starts
void UInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < ActorsWithReactables.Num(); i++)
	{
		TArray<UBaseReactableComponent*> comps;
		ActorsWithReactables[i]->GetComponents(comps);
		UE_LOG(LogTemp, Log, TEXT("Debug1 : %d"), comps.Num());
		for (int j = 0; j < comps.Num(); j++)
		{
			Reactables.Add(comps[j]);
		}
	}
	
}

FString UInteractableBase::GetDescription()
{
	//return Description;
	if (Reactables.Num() > 0)
	{
		return Reactables[0]->GetDescription();
	}
	return Description;
}

void UInteractableBase::OnInteract()
{
	UE_LOG(LogTemp, Log, TEXT("Interacting"));
	UE_LOG(LogTemp, Log, TEXT("Num: %d"), Reactables.Num());
	for (int i = 0; i < Reactables.Num(); i++)
	{
		//Reactables[i]->TriggerReaction();
	}
}

// Called every frame
void UInteractableBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

