// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInstigatorComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Components/SlateWrapperTypes.h"

// Sets default values for this component's properties
UBaseInstigatorComponent::UBaseInstigatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1f;

	InteractionReach = 200.f;
	InteractInputName = "Interact";

	// Hud
	InteractionTextboxVisibilityHud = ESlateVisibility::Hidden;
	InteractionTextboxTextHud = "";

	CurrentInteractable = nullptr;

}


void UBaseInstigatorComponent::SetupInputBindings_Implementation(UInputComponent* PlayerInputComponent)
{
	//ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	UE_LOG(LogTemp, Log, TEXT("Its a start!"))
	//if (NewController != nullptr && NewController->InputComponent != nullptr)
	//if (OwnerCharacter != nullptr && OwnerCharacter->IsPlayerControlled() && OwnerCharacter->InputComponent != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Ofcourse mams!"))
			//NewController->InputComponent->GetActionBinding()
			PlayerInputComponent->BindAction(InteractInputName, IE_Pressed, this, &UBaseInstigatorComponent::InteractWithInteractable);
		//NewController->InputComponent->BindAction(InteractInputName, IE_Pressed, this, &UBaseInstigatorComponent::InteractWithInteractable);
		//OwnerCharacter->InputComponent->BindAction(InteractInputName, IE_Pressed, this, &UBaseInstigatorComponent::InteractWithInteractable);
	}
}

void UBaseInstigatorComponent::InteractWithInteractable()
{
	UE_LOG(LogTemp, Log, TEXT("Instigateing 1"));
	if (CurrentInteractable != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Instigateing 2"));
		CurrentInteractable->OnInteract(this);
		InteractionTextboxTextHud = CurrentInteractable->GetDescription(); // In case interacting with it, has caused it to change description
	}
}

// Called when the game starts
void UBaseInstigatorComponent::BeginPlay()
{
	Super::BeginPlay();

	//ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	//if (OwnerCharacter != nullptr && OwnerCharacter->IsPlayerControlled())
	//{
	//	OwnerCharacter->InputComponent->BindAction(InteractInputName, IE_Pressed, this, &UBaseInstigatorComponent::InteractWithInteractable);
	//}

	TArray<UCameraComponent*> CameraComps;
	GetOwner()->GetComponents(CameraComps);
	if (CameraComps.Num() > 0)
	{
		PosComponent = Cast<USceneComponent>(CameraComps[0]);
	}
	else
	{
		PosComponent = nullptr;
	}
	
}

void UBaseInstigatorComponent::CheckForInteractable()
{
	struct FHitResult OutHit;
	FVector Start = PosComponent->GetComponentLocation();
	FVector End = Start + PosComponent->GetForwardVector() * InteractionReach;

	bool FoundInteractable = false;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		//TArray<UBaseInteractableComponent*> Comps;
		//OutHit.GetActor()->GetComponents(Comps);
		TArray<USceneComponent*> Comps;
		OutHit.GetComponent()->GetChildrenComponents(false, Comps);
		//if (Comps.Num() > 0)
		for (int i = 0; i < Comps.Num(); i++)
		{
			if (Comps[i]->IsA(UBaseInteractableComponent::StaticClass()))
			{
				UBaseInteractableComponent* Interactable = Cast<UBaseInteractableComponent>(Comps[i]);
				FoundInteractable = true;
				//UE_LOG(LogTemp, Log, TEXT("Looking at: %s"), *Interactable->GetDescription());
				if (Interactable != CurrentInteractable)
				{
					CurrentInteractable = Interactable;
					InteractionTextboxTextHud = Interactable->GetDescription();
					InteractionTextboxVisibilityHud = ESlateVisibility::Visible;
				}
				break;
			}
		}
	}
	if (!FoundInteractable && CurrentInteractable != nullptr)
	{
		CurrentInteractable = nullptr;
		InteractionTextboxVisibilityHud = ESlateVisibility::Hidden;
	}
}


// Called every frame
void UBaseInstigatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PosComponent != nullptr)
	{
		CheckForInteractable();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Error! BaseInsigatorComp does not have a PosComponent set. (Should not tick at all)"));
	}
}

