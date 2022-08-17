// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "LevelSequenceActor.h"
//#include "ActorSequenceComponent.h"
#include "BaseReactableComponent.generated.h"

class UBaseInstigatorComponent;
class UBaseInteractableComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEGAME_API UBaseReactableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseReactableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	//UPROPERTY(EditAnywhere, Category = Test)
	//bool activateTest;

	//bool lastActive;

	//UMovieSceneSequencePlayer* ReactionPlayer;

	//bool AlteredState;

	//UPROPERTY(EditAnywhere, Category = Interact)
	//FString StageOne;

	//UPROPERTY(EditAnywhere, Category = Interact)
	//FString StageTwo;

	//UPROPERTY(EditAnywhere, Category = Sequence)
	//UActorSequenceComponent* Sequence;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void TriggerReaction(UBaseInstigatorComponent* instigator, UBaseInteractableComponent* interactable) {}

	virtual FString GetDescription() { return "Interact"; }
};
