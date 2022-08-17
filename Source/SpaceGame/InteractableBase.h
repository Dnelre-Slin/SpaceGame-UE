// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseReactableComponent.h"
#include "InteractableBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEGAME_API UInteractableBase : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Description)
	FString Description;

public:	
	// Sets default values for this component's properties
	UInteractableBase();

	/** Return Description */
	virtual FString GetDescription();

	/** On interact event */
	virtual void OnInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Interact)
	TArray<AActor*> ActorsWithReactables;

	TArray<UBaseReactableComponent*> Reactables;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
