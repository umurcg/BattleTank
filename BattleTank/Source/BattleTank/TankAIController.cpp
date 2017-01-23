// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"




ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto pawnedTank = GetControlledTank();
	if (pawnedTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("I posses %s"), *(pawnedTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("I dont possess a tank"));
	}
}
