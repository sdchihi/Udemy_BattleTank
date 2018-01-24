// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"




void UTankBarrel::Elevate(float relativeSpeed) {
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);
	auto elevationChange = relativeSpeed * maxDegreePerSecond * GetWorld()->DeltaTimeSeconds; 
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto elevation = FMath::Clamp<float>(rawNewElevation, minElevationDegrees, maxElevationDegrees);

	//UE_LOG(LogTemp, Warning, L"%f", elevation)

	SetRelativeRotation(FRotator(elevation, 0, 0));
}
