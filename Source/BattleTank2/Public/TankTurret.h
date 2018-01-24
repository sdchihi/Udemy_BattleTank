// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK2_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void RotateTurret(float relativeValue);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxRotatingPerSecond = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	float maxRotationDegrees = 90;

	UPROPERTY(EditAnywhere, Category = Setup)
	float minRotationDegrees = 0;
};
