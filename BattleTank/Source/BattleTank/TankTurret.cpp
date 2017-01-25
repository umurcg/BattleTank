// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"




void UTankTurret::RotateTurret(float RelativeSpeed)
{
	
	
	float rotationDegree = FMath::Clamp<float>(RelativeSpeed, -1, 1)*maxDegreePerSecond*(GetWorld()->DeltaTimeSeconds);
	FRotator newRotation = FRotator(0, (RelativeRotation.Yaw + rotationDegree), 0);
	
	SetRelativeRotation(newRotation);

	
}
