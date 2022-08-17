// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputBindingComponentInterface.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class SPACEGAME_API UInputBindingComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class SPACEGAME_API IInputBindingComponentInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InputBinding")
    void SetupInputBindings(UInputComponent* PlayerInputComponent);
};
