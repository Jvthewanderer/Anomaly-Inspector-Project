// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "insAnomalyListeners.generated.h"

class UinsAnomalyManager;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeactivateAnomalyDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateAnomalyDelegate, FGameplayTag, AnomalyTag);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INSPECTPRJ_API UinsAnomalyListeners : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UinsAnomalyListeners();

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	bool SetAnomalyActive(bool isActive);

	UFUNCTION(BlueprintPure, Category = "Anomaly")
	bool GetAnomalyActive() { return AnomalyActive; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void OnAnomalyCalled(FGameplayTag AnomalyTag);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTag ActorAnomalyTag;

	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	bool AnomalyActive;

	UinsAnomalyManager* AnomalyManager;

public:	

	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Anomaly")
	FActivateAnomalyDelegate OnActivateAnomalyDelegate;

	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Anomaly")
	FDeactivateAnomalyDelegate OnDeactivateAnomalyDelegate;

		
};
