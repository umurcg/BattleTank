// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "TankPlayerController.generated.h" //Must be the last include

class UTank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:


	ATank* GetControlledTank() const;
	
	
	void BeginPlay() override;
	void Tick(float) override;
	void AimTowardsCrossHair();
	
	bool GetSightRayHitLocation(FVector& hit) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &lookDirection) const;

	bool GetLookVectorHitLocation(FVector &HitLocation, FVector lookDirection) const;

	//This variabvles hsould be changed when dot in the ui system is changed.
	UPROPERTY(EditAnywhere)
		float crossHairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere)
		float crossHairYLocation = 0.333333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f; //10km
};
