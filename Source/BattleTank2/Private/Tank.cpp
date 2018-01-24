// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

float ATank::GetHealthPercent()
{
	return (float)currentHealth / (float)startingHealth;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = startingHealth;
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {

	// 부동소수점
	int32 damagePoint = FPlatformMath::RoundToInt(DamageAmount);
	auto damageToApply = FMath::Clamp(damagePoint, 0, currentHealth);

	currentHealth -= damageToApply;

	if (currentHealth <= 0) {
		OnDeath.Broadcast();
		GetWorld()->GetFirstPlayerController()->StartSpectatingOnly();
	}
	
	return damageToApply;
}

