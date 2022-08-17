// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseInteractableComponent.generated.h"

class UBaseInstigatorComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEGAME_API UBaseInteractableComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/** Return Description */
	virtual FString GetDescription() { return "Interact"; }

	/** On interact event */
	virtual void OnInteract(UBaseInstigatorComponent* instigator) {}
		
};
