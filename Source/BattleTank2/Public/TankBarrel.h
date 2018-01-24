// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories =("Collision"))
class BATTLETANK2_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float relativeSpeed);
	
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreePerSecond = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationDegrees = 0;
	
};
