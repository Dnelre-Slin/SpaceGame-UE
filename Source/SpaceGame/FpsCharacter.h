// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "InputCoreTypes.h"
//#include "Components/SlateWrapperTypes.h"
//#include "InteractableBase.h"
#include "FpsCharacter.generated.h"

UCLASS()
class SPACEGAME_API AFpsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	// Sets default values for this character's properties
	AFpsCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/** Swap to fps character pawn */
	void SwapPawn();

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	///** Interact with CurrentInteractable object */
	//void InteractWithInteractable();

	UFUNCTION(BlueprintImplementableEvent)
	void Batfly(AActor* hitObject);

	//// Begin HUD variables
	///** The visibility state of the interaction textbox hud element*/
	//UPROPERTY(Category = Hud, BlueprintReadOnly)
	//ESlateVisibility InteractionTextboxVisibilityHud;

	///** The text of the interaction textbox hud element*/
	//UPROPERTY(Category = Hud, BlueprintReadOnly)
	//FString InteractionTextboxTextHud;
	//// End HUD variables

	//UInteractableBase* CurrentInteractable;
private:

	///** Interaction reach */
	//UPROPERTY(Category = Interaction, EditAnywhere)
	//float InteractionReach;

	/** SpaceshipPawn */
	UPROPERTY(Category = Pawns, EditAnywhere)
	APawn* SpaceshipPawn;

	///** Function for checking if an interactable object is in front of the fps character */
	//void CheckForInteractable();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
