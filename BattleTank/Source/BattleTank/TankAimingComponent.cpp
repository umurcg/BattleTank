// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float LaunchSpeed)
{
	if (!Barrel||!Turret) return;

	FVector tossVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("FirePoint"));

	////Calculate the outLaunchVelocity
	if (!UGameplayStatics::SuggestProjectileVelocity(GetWorld(), tossVelocity, startLocation, hitLocation, LaunchSpeed,false,0,0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		//UE_LOG(LogTemp, Warning, TEXT("%f: no aim solution "), GetWorld()->GetRealTimeSeconds());
		return;
	}

	auto AimDirection = tossVelocity.GetSafeNormal();


	FString name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%f: aim solution is: %s , name is %s"),  GetWorld()->GetRealTimeSeconds(), *name ,*(AimDirection.ToString()));

	MoveBarrelTowards(AimDirection);



}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) const
{
	//Work out difference betweeen current barrel rotation and Aim Direction
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = aimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//Move the barrel the right amount this frame
	//UE_LOG(LogTemp, Warning, TEXT("Delta is  %s"), *(DeltaRotator.ToString()));
	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->RotateTurret(DeltaRotator.Yaw);

	//Given a max elevation speed and a frame time


}



void UTankAimingComponent::setBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::setTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;

}

