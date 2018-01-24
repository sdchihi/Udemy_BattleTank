// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// 제일 마지막에 Include 되어야 한다.

class UAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	void BeginPlay() override;

	void SetPawn(APawn * InPawn);

	UFUNCTION()
	void OnPossessedTankDeath();

	virtual void Tick(float DeltaTime) override;
	
	// Crosshair 방향으로 포신을 돌림
	void AimTowardCrosshair();

	// Return an out parameter , true if hit landscape
	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;


protected:


	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UAimingComponent* aimCompRef);
};
