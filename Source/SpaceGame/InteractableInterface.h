// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableInterface.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class SPACEGAME_API UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class SPACEGAME_API IInteractableInterface
{
	GENERATED_BODY()

public:

	FString GetDescription();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteract();
};