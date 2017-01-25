// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void RotateTurret(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreePerSecond = 10.f;
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxSpeedRotation = 10.f;
	UPROPERTY(EditAnywhere, Category = Setup)
	float minSpeedRotation = -10.f;
	
};
