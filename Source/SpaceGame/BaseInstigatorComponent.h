// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseInteractableComponent.h"
#include "InputBindingComponentInterface.h"
#include "BaseInstigatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEGAME_API UBaseInstigatorComponent : public UActorComponent, public IInputBindingComponentInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseInstigatorComponent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Broadcast")
	void SetupInputBindings(UInputComponent* PlayerInputComponent);  // This is the prototype declared in the interface
	virtual void SetupInputBindings_Implementation(UInputComponent* PlayerInputComponent) override; // This is the declaration of the implementation

	/** Interact with CurrentInteractable object */
	void InteractWithInteractable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Function for checking if an interactable object is in front of the fps character */
	void CheckForInteractable();

	/** Interaction reach */
	UPROPERTY(Category = Interaction, EditAnywhere)
	float InteractionReach;

	/** Interaction reach */
	UPROPERTY(Category = KeyBindings, EditAnywhere)
	FName InteractInputName;

	// Begin HUD variables
	/** The visibility state of the interaction textbox hud element*/
	UPROPERTY(Category = Hud, BlueprintReadOnly)
	ESlateVisibility InteractionTextboxVisibilityHud;

	/** The text of the interaction textbox hud element*/
	UPROPERTY(Category = Hud, BlueprintReadOnly)
	FString InteractionTextboxTextHud;
	// End HUD variables

	UBaseInteractableComponent* CurrentInteractable;

	USceneComponent* PosComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
