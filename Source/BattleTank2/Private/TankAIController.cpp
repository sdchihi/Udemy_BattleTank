// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "AimingComponent.h"
#include "Tank.h"				//OnDeath

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();

	if (!ensure(playerTank && controlledTank)) { return; }
		
	MoveToActor(playerTank, acceptableRadius);

	auto aimingComponent = controlledTank->FindComponentByClass<UAimingComponent>();
	if (!ensure(aimingComponent)) { return; }
	aimingComponent->AimAt(playerTank->GetActorLocation());
		


	if (aimingComponent->GetFiringState() == EFiringState::Locked) {
		aimingComponent->Fire();
	}

	
}


void ATankAIController::SetPawn(APawn* InPawn) {

	Super::SetPawn(InPawn);
	if (InPawn) {
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }

		//TODO
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}



