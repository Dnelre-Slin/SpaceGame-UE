// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseReactableComponent.h"
#include "InputBindingComponentInterface.h"
#include "PossessionReactableComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACEGAME_API UPossessionReactableComponent : public UBaseReactableComponent, public IInputBindingComponentInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UPossessionReactableComponent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputBindings")
	void SetupInputBindings(UInputComponent* PlayerInputComponent);  // This is the prototype declared in the interface
	virtual void SetupInputBindings_Implementation(UInputComponent* PlayerInputComponent) override; // This is the declaration of the implementation

	virtual void TriggerReaction(UBaseInstigatorComponent* instigator, UBaseInteractableComponent* interactable) override;
	void Unpossess();

	virtual void Activate(bool bReset) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupBindings();

	APawn* PawnOwner;
	APawn* PawnPossessor;

	/** Input for TurnPitch */
	UPROPERTY(Category = InputBindings, EditAnywhere)
	FName ExitVehicleInputBinding;
};
