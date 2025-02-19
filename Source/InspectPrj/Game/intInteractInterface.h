// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "intInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UintInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSPECTPRJ_API IintInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void StartInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DisplayInteractableActor(FVector Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void StartPlaceCleaner();

};
