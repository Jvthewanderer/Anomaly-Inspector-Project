// Fill out your copyright notice in the Description page of Project Settings.


#include "insAnomalyListeners.h"
#include "insAnomalyManager.h"
#include "GameFramework/GameModeBase.h"
#include "../Game/insAnomalyInterface.h"

// Sets default values for this component's properties
UinsAnomalyListeners::UinsAnomalyListeners()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


bool UinsAnomalyListeners::SetAnomalyActive(bool isActive)
{
	AnomalyActive = isActive;

	if (!AnomalyActive) {

		if (GetOwner()->GetClass()->ImplementsInterface(UinsAnomalyInterface::StaticClass()))
		{
			IinsAnomalyInterface::Execute_ResetAnomaly(GetOwner());
		}

		OnDeactivateAnomalyDelegate.Broadcast();
		if (AnomalyManager) {
			AnomalyManager->RemoveAnomaly(ActorAnomalyTag);
		}

	}

	return AnomalyActive;
}

// Called when the game starts
void UinsAnomalyListeners::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AnomalyManager = Cast<UinsAnomalyManager>(GetWorld()->GetAuthGameMode()->GetComponentByClass(UinsAnomalyManager::StaticClass()));
	if (AnomalyManager)
	{
		AnomalyManager->OnUpdateAnomalyDelegate.AddDynamic(this, &UinsAnomalyListeners::OnAnomalyCalled);
	}
	
}

void UinsAnomalyListeners::OnAnomalyCalled(FGameplayTag AnomalyTag)
{
	if (ActorAnomalyTag.MatchesTag(AnomalyTag)) {

		if (GetOwner()->GetClass()->ImplementsInterface(UinsAnomalyInterface::StaticClass()))
		{
			IinsAnomalyInterface::Execute_StartAnomaly(GetOwner());
		}
		OnActivateAnomalyDelegate.Broadcast(AnomalyTag);
		SetAnomalyActive(true);
	}
}
