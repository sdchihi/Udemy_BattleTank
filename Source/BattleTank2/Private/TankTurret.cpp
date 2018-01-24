// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"




void UTankTurret::RotateTurret(float relativeValue) {

	relativeValue = FMath::Clamp<float>(relativeValue, -1, +1);
	auto rotationChange = relativeValue * maxRotatingPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newRotation = RelativeRotation.Yaw + rotationChange;
	
//	UE_LOG(LogTemp, Warning, L"%f", rawNewRotation)
	SetRelativeRotation(FRotator(0, newRotation, 0));


}