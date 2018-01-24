// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "AimingComponent.h"
#include "Tank.h"

void ATankPlayerController::SetPawn(APawn* InPawn) {

	Super::SetPawn(InPawn);
	if (InPawn) {
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }

		//TODO
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath() {
	StartSpectatingOnly();
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto aimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	if (!ensure(aimingComponent)) { return; }
	FoundAimingComponent(aimingComponent);
}


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AimTowardCrosshair();
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetPawn()) { return; }
	auto aimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	FVector hitLocation; // out parameter
	bool bGotHitLocation = GetSightRayHitLocation(hitLocation);
	if (bGotHitLocation) {

		aimingComponent->AimAt(hitLocation);
		//UE_LOG(LogTemp, Warning, L"Hit location : %s", *hitLocation.ToString());
		// Crosshair�� ����Ű�� ������ linetrace�� �̿��� ���� ��ǥ�� ����.
	}
	
}

//Crosshair�� ����Ű�� ������ linetrace�� landscape�� �浹�ϴ��� ����
bool ATankPlayerController::GetSightRayHitLocation(FVector & outHitLocation) const
{
	//outHitLocation = 
	
	// Crosshair ������ ã�´�
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	auto screenLocation = FVector2D(viewportSizeX * CrosshairXLocation, viewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, L"Screen Location : %s", *screenLocation.ToString());

	  
	//"De-project" ȭ����� Crosshair�������� World direction���� 
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection)) {
		return GetLookVectorHitLocation(lookDirection, outHitLocation);

	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const 
{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility)) 
	{
		hitLocation = hitResult.Location;

		return true;
	}
	hitLocation = FVector(0);
	return false;
};

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector cameraWorldLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraWorldLocation, LookDirection);
	return true;
}


