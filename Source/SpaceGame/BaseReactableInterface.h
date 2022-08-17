// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseReactableInterface.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class SPACEGAME_API UBaseReactableInterface : public UInterface
{
    GENERATED_BODY()
};

class SPACEGAME_API IBaseReactableInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
    void TriggerReaction();
};