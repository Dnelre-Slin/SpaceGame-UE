// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseReactableComponent.h"

// Sets default values for this component's properties
UBaseReactableComponent::UBaseReactableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//activateTest = false;
	//lastActive = false;

	//AlteredState = false;

	//StageOne = "Interact";
	//StageTwo = "Interact";

	//ReactionPlayer = nullptr;
}


// Called when the game starts
void UBaseReactableComponent::BeginPlay()
{
	Super::BeginPlay();

	//ReactionPlayer = nullptr;

	//ALevelSequenceActor* sequenceOwner = Cast<ALevelSequenceActor>(GetOwner());
	//if (Sequence != nullptr)
	//{
	//	//UE_LOG(LogTemp, Log, TEXT("Dedug1"));
	//	ReactionPlayer = Sequence->GetSequencePlayer();
	//}
	//else
	//{
	////	AActor* owner = GetOwner();
	////	if (owner != nullptr)
	////	{
	////		owner->GetComponentByClass()
	////	}
	//}
}


//// Called every frame
//void UBaseReactableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	//UE_LOG(LogTemp, Log, TEXT("Hmm"));
//	//if (activateTest != lastActive)
//	//{
//	//	ALevelSequenceActor* sequenceOwner = Cast<ALevelSequenceActor>(GetOwner());
//	//	if (sequenceOwner != nullptr)
//	//	{
//	//		if (activateTest)
//	//		{
//	//			UE_LOG(LogTemp, Log, TEXT("Open"));
//	//			sequenceOwner->GetSequencePlayer()->Play();
//	//		}
//	//		else
//	//		{
//	//			UE_LOG(LogTemp, Log, TEXT("Close"));
//	//			sequenceOwner->GetSequencePlayer()->PlayReverse();
//	//		}
//	//	}
//
//	//	lastActive = activateTest;
//	//}
//}

//void UBaseReactableComponent::TriggerReaction()
//{
//	UE_LOG(LogTemp, Log, TEXT("Reaction 1"));
//	if (ReactionPlayer != nullptr)
//	{
//		UE_LOG(LogTemp, Log, TEXT("Reaction 2"));
//		if (!AlteredState)
//		{
//			ReactionPlayer->Play();
//			AlteredState = true;
//		}
//		else
//		{
//			ReactionPlayer->PlayReverse();
//			AlteredState = false;
//		}
//	}
//}
//
//FString UBaseReactableComponent::GetDescription()
//{
//	if (AlteredState)
//	{
//		return StageTwo;
//	}
//	else
//	{
//		return StageOne;
//	}
//}

