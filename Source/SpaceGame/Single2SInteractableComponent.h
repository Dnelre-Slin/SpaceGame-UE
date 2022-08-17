// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractableComponent.h"
#include "BaseReactableComponent.h"
#include "BaseInstigatorComponent.h"
#include "Single2SInteractableComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACEGAME_API USingle2SInteractableComponent : public UBaseInteractableComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	USingle2SInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Description)
	FString Description;

	UPROPERTY(EditAnywhere, Category = Interact)
	AActor* ActorWithReactable;

	//UPROPERTY(EditAnywhere, Category = Interact)
	UPROPERTY()
	UBaseReactableComponent* Reactable;

public:
	/** Return Description */
	virtual FString GetDescription() override;

	/** On interact event */
	virtual void OnInteract(UBaseInstigatorComponent* instigator) override;

	UFUNCTION(BlueprintCallable)
	virtual void SetReactable(UBaseReactableComponent* NewReactable) { Reactable = NewReactable; }
};
