// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto pawnedTank = GetControlledTank();
	if (pawnedTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Pawned tank is: %s"), *(pawnedTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("There is no initilized pawned tank!"));
	}
}




ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

