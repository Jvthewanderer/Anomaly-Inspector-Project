// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "insAnomalyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UinsAnomalyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INSPECTPRJ_API IinsAnomalyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Anomaly")
	void StartAnomaly();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Anomaly")
	void ResetAnomaly();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Anomaly")
	void TriggerAnomaly();
};
