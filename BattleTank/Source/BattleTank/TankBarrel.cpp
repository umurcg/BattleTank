// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"



//-1 is max dawnard speed and 1 is max upward speed
void UTankBarrel::Elevate(float RelativeSpeed) 
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, +1.f);
	auto ElevationChange = RelativeSpeed*MaxDegreePerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawNewElvation = RelativeRotation.Pitch + ElevationChange;
	auto clampedElevation=FMath::Clamp<float>(RawNewElvation, minElevation, maxElevation);

	SetRelativeRotation(FRotator(clampedElevation, 0, 0));

}
