// Fill out your copyright notice in the Description page of Project Settings.

#include "PossessionReactableComponent.h"
#include "BaseInstigatorComponent.h"


UPossessionReactableComponent::UPossessionReactableComponent()
{
	PawnPossessor = nullptr;
	PawnOwner = nullptr;

	ExitVehicleInputBinding = "ExitVehicle";


}

void UPossessionReactableComponent::BeginPlay()
{
	PawnOwner = Cast<APawn>(GetOwner());
	SetupBindings();
	UE_LOG(LogTemp, Log, TEXT("Beggining play on possess react"))
}

void UPossessionReactableComponent::SetupBindings()
{
	//if (PawnOwner != nullptr && PawnOwner->IsPlayerControlled())
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Ofcourse sirs!"))
	//	PawnOwner->InputComponent->BindAction(ExitVehicleInputBinding, IE_Pressed, this, &UPossessionReactableComponent::Unpossess);
	//}
}

void UPossessionReactableComponent::SetupInputBindings_Implementation(UInputComponent* PlayerInputComponent)
{
	//UE_LOG(LogTemp, Log, TEXT("Is that so? %s"), (PlayerInputComponent != nullptr)?TEXT("true"):TEXT("false"))
	//if (PawnOwner != nullptr && PawnOwner->IsPlayerControlled())
	{
		UE_LOG(LogTemp, Log, TEXT("Ofcourse sirs! %s"), (PawnOwner->InputComponent != nullptr) ? TEXT("true") : TEXT("false"))
		PlayerInputComponent->BindAction(ExitVehicleInputBinding, IE_Pressed, this, &UPossessionReactableComponent::Unpossess);
		//PawnOwner->InputComponent->BindAction(ExitVehicleInputBinding, IE_Pressed, this, &UPossessionReactableComponent::Unpossess);
	}
}

void UPossessionReactableComponent::TriggerReaction(UBaseInstigatorComponent* instigator, UBaseInteractableComponent* interactable)
{
	if (PawnOwner)
	{
		PawnPossessor = Cast<APawn>(instigator->GetOwner());
		if (PawnPossessor)
		{
			AController* controller = PawnPossessor->GetController();
			if (controller != nullptr)
			{
				controller->Possess(PawnOwner);
				SetupBindings();
			}
		}
	}
}

void UPossessionReactableComponent::Unpossess()
{
	UE_LOG(LogTemp, Log, TEXT("Unpossessiong!"))
	if (PawnOwner != nullptr && PawnPossessor != nullptr)
	{
		AController* controller = PawnOwner->GetController();
		if (controller != nullptr)
		{
			controller->Possess(PawnPossessor);
		}
	}
}

void UPossessionReactableComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	UE_LOG(LogTemp, Log, TEXT("Comp activated"))
}
