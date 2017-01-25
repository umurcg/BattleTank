// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
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

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrossHair();
}

//Aims barrel to cross hair aim
void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) return;

	FVector hitLocation; //Out parameter
	
	/// Get World location through cross hair
	if (GetSightRayHitLocation(hitLocation)) {

		// If it hits something
		GetControlledTank()->AimAt(hitLocation);
		//Tell the controlled tank to aim that position
	}

}
		

//Gets hit location of cross hair
bool ATankPlayerController::GetSightRayHitLocation(FVector & hit) const
{
	///Find the crosshair position
	int32 size_x, size_y;
	GetViewportSize(size_x, size_y);
	FVector2D ScreenLocation = FVector2D(size_x*crossHairXLocation, size_y*crossHairYLocation);

	///Find direction of aim in 3d world space in unit vector
	FVector lookDirection;
	if (!GetLookDirection(ScreenLocation, lookDirection)) return false;

	///Get hit location with look direction
	if(!GetLookVectorHitLocation(hit,lookDirection)) return false;
	
	//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *hit.ToString())

	return true;
}


//Gets direction of cross hair
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &lookDirection) const
{

	FVector camPosition; //Wont be used

	//De-project the screen position of the crosshair tor a world direction
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, camPosition, lookDirection);
	return true;
}


//Get hit location through look direction from camera psoition. Max distance is lineTraceRange
bool ATankPlayerController::GetLookVectorHitLocation(FVector &HitLocation, FVector lookDirection) const
{
	//Line-trace along the look direction and see what we hit

	//Find camera position
	auto StartLocation = PlayerCameraManager->GetCameraLocation();

	//Find end position
	FVector endPosition = StartLocation+ lookDirection*LineTraceRange;

	FHitResult fhit;

	//Create linetrace to distance
	if(!GetWorld()->LineTraceSingleByChannel(fhit, StartLocation, endPosition, ECC_Visibility)) return false;

	HitLocation = fhit.Location;

	return true;
}

//Gets tank that are controled by this player controller
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

