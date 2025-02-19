// Fill out your copyright notice in the Description page of Project Settings.


#include "insAnomalyManager.h"
#include "../Gameplay/insAnomalyTrigger.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UinsAnomalyManager::UinsAnomalyManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UinsAnomalyManager::BeginPlay()
{
	Super::BeginPlay();

	InitAnomaliesManager();
	
}

void UinsAnomalyManager::InitAnomaliesManager()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AinsAnomalyTrigger::StaticClass(), OutActors);

	for (AActor* currentActors : OutActors) {
		if (AinsAnomalyTrigger* AnomolyTrigger = Cast<AinsAnomalyTrigger>(currentActors))
		{
			AnomolyTriggers.Add(AnomolyTrigger);
		}
	}
}

bool UinsAnomalyManager::SetAnomalyGame(bool bStart)
{
	bAnomalyStart = bStart;
	return bAnomalyStart;
}

bool UinsAnomalyManager::CallOnAnomaly(FString TriggerAnomalyName)
{
	if (bAnomalyStart)
	{
		if (AnomalyTags.Contains(TriggerAnomalyName)) {

			FGameplayTag CurrentAnomalyTag = *AnomalyTags.Find(TriggerAnomalyName);

			if (!ActiveAnomalies.Contains(CurrentAnomalyTag)) {

				ActiveAnomalies.Add(CurrentAnomalyTag);

				OnUpdateAnomalyDelegate.Broadcast(CurrentAnomalyTag);
				OnCheckAnomaltyDelegate.Broadcast();
				return true;
			}
		}
	}
	else {
		//Anomaly Not Started.
	}

	return false;
}

bool UinsAnomalyManager::RemoveAnomaly(FGameplayTag AnomalyTag)
{

	if (ActiveAnomalies.Contains(AnomalyTag))
	{
		ActiveAnomalies.Remove(AnomalyTag);

		OnCheckAnomaltyDelegate.Broadcast();

		return true;
	}

	return false;
}

