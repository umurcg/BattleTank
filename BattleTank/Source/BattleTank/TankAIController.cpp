// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto playerTank = GetPlayerTank();
	if (playerTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player tank is %s"), *(playerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player tank"));
	}
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	ATank* playerTank = GetPlayerTank();
	ATank* controlledTank = GetControlledTank();
	if (!playerTank || !playerTank) return;

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerTank= GetWorld()->GetFirstPlayerController()-> GetPawn();
	if (playerTank == nullptr) return nullptr;
	
	ATank* castedPT = Cast<ATank>(playerTank);

	return castedPT;

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}