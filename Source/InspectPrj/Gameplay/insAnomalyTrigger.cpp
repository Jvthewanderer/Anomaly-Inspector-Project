// Fill out your copyright notice in the Description page of Project Settings.


#include "insAnomalyTrigger.h"
#include "Components/BoxComponent.h"
#include "../InspectPrjCharacter.h"
#include "../Component/insAnomalyListeners.h"

// Sets default values
AinsAnomalyTrigger::AinsAnomalyTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AnomolyTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("AnomolyTrigger"));
	RootComponent = AnomolyTrigger;

}

// Called when the game starts or when spawned
void AinsAnomalyTrigger::BeginPlay()
{
	Super::BeginPlay();

	AnomolyTrigger->OnComponentBeginOverlap.AddDynamic(this, &AinsAnomalyTrigger::OnBeginOverlap);
	AnomolyTrigger->OnComponentEndOverlap.AddDynamic(this, &AinsAnomalyTrigger::OnEndOverlap);

	TArray<AActor*> OutActors;
	AnomolyTrigger->GetOverlappingActors(OutActors);

	for (AActor* currentActor : OutActors) {
		if (currentActor->FindComponentByClass(UinsAnomalyListeners::StaticClass())) {
			AnomolyActors.Add(currentActor);
		}
	}
	
}

void AinsAnomalyTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == AInspectPrjCharacter::StaticClass()) {
		PlayerInTrigger = true;
	}
}

void AinsAnomalyTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass() == AInspectPrjCharacter::StaticClass())
	{
		TArray<AActor*> OutActors;
		AnomolyTrigger->GetOverlappingActors(OutActors, AInspectPrjCharacter::StaticClass());
		if(OutActors.Num() <= 0)
		{
			PlayerInTrigger = false;
		}
	}
}

bool AinsAnomalyTrigger::CheckForActiveAnomaly()
{
	TArray<AActor*> OutActors;
	AnomolyTrigger->GetOverlappingActors(OutActors);

	bool foundActiveAnomalys = false;
	for (AActor* currentActor : OutActors) {
		if (UinsAnomalyListeners* currentListener = Cast<UinsAnomalyListeners>(currentActor->FindComponentByClass(UinsAnomalyListeners::StaticClass()))) {
			
			if (currentListener->GetAnomalyActive())
			{
				currentListener->SetAnomalyActive(false);
				foundActiveAnomalys = true;
			}

		}
	}

	return foundActiveAnomalys;
}

// Called every frame
void AinsAnomalyTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}