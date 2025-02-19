// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "insAnomalyTrigger.generated.h"

class UBoxComponent;
class UPrimitiveComponent;

UCLASS()
class INSPECTPRJ_API AinsAnomalyTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AinsAnomalyTrigger();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UBoxComponent> AnomolyTrigger;

	UFUNCTION(BlueprintPure, Category = "Anomaly")
	bool GetPlayerInTrigger() { return PlayerInTrigger; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	bool CheckForActiveAnomaly();

	TArray<TObjectPtr<AActor>> AnomolyActors;

	bool PlayerInTrigger = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
