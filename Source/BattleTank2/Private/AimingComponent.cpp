// Fill out your copyright notice in the Description page of Project Settings.
#include "AimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	lastReloadTime = FPlatformTime::Seconds();

}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//Barrel = GetOwner()->FindComponentByClass<UTankBarrel>();
}

void UAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	turret = TurretToSet;
}



// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (!ensure(Barrel)) { return; }				// todo
	
	if (roundLeft <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastReloadTime) < reloadInterval) {
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving()){
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
	
}




void UAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
	}
	// If no solution found do nothing
}



void UAimingComponent::MoveBarrelToward(FVector aimDirection) 
{
	if (!ensure(Barrel) || !ensure(turret)) { return; }
	
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	if (FMath::Abs(deltaRotator.Yaw) < 180) {
		turret->RotateTurret(deltaRotator.Yaw);
	}
	else {
		turret->RotateTurret(-deltaRotator.Yaw);

	}
} 

void UAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }				// todo
	bool isReloaded = (FPlatformTime::Seconds() - lastReloadTime) > reloadInterval;
	if (FiringState == EFiringState::Locked  || FiringState == EFiringState::Aiming) {

		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->Launch(launchSpeed);
		lastReloadTime = FPlatformTime::Seconds();
		roundLeft--;
	}
}



bool UAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto barrelForward = Barrel->GetForwardVector();
	
	return !barrelForward.Equals(AimDirection, 0.01);
}


EFiringState UAimingComponent::GetFiringState() const {
	return FiringState;
}

int32 UAimingComponent::GetRoundLeft() const
{
	return roundLeft;
}
