// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "insAnomalyManager.generated.h"

class AinsAnomalyTrigger;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateAnomalyDelegate, FGameplayTag, AnomalyTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCheckAnomalyDelegate);


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INSPECTPRJ_API UinsAnomalyManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UinsAnomalyManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	TArray<TObjectPtr<AinsAnomalyTrigger>> AnomolyTriggers;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Anomaly")
	TMap<FString, FGameplayTag> AnomalyTags;

	UPROPERTY()
	TArray<FGameplayTag> ActiveAnomalies;

	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	bool bAnomalyStart = false;

public:	

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void InitAnomaliesManager();

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	bool SetAnomalyGame(bool bStart);

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	bool CallOnAnomaly(FString TriggerAnomoly);

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	bool RemoveAnomaly(FGameplayTag AnomalyTag);

	UFUNCTION(BlueprintPure, Category = "Anomaly")
	int32 GetActiveAnomalies() { return ActiveAnomalies.Num(); }

	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Anomaly")
	FUpdateAnomalyDelegate OnUpdateAnomalyDelegate;

	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Anomaly")
	FCheckAnomalyDelegate OnCheckAnomaltyDelegate;

		
};
