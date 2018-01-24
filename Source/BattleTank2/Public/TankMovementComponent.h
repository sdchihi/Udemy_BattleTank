// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 *  주행중 트랙에 관한것
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK2_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	

public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float throwValue);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float throwValue);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:

	UTankTrack* leftTrack = nullptr;
	UTankTrack* rightTrack = nullptr;
};
