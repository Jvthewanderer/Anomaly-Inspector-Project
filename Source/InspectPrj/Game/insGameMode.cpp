// Fill out your copyright notice in the Description page of Project Settings.


#include "insGameMode.h"
#include "../Component/insAnomalyManager.h"

AinsGameMode::AinsGameMode()
	: Super()
{

	AnomolyManager = CreateDefaultSubobject<UinsAnomalyManager>(TEXT("AnomolyManager"));
}
