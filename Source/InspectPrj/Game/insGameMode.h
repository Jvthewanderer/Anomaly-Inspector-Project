// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "insGameMode.generated.h"

class UinsAnomalyManager;

/**
 * 
 */
UCLASS()
class INSPECTPRJ_API AinsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AinsGameMode();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TObjectPtr<UinsAnomalyManager> AnomolyManager;
	
};
