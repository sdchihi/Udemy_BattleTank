// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet) {

	if (!ensure(leftTrackToSet || !rightTrackToSet)) { return; }
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float throwValue) {
	if (!ensure(leftTrack || !rightTrack)) { return; }
	leftTrack->SetThrottle(throwValue);
	rightTrack->SetThrottle(throwValue);
}


void UTankMovementComponent::IntendTurnRight(float throwValue) {
	if (!ensure(leftTrack || !rightTrack)){ return; }
	leftTrack->SetThrottle(throwValue);
	rightTrack->SetThrottle(-throwValue);
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto forwardThrow = FVector::DotProduct(tankForward, AIForwardIntention);

	auto rightThrow = FVector::CrossProduct(tankForward, AIForwardIntention).Z;

	IntendMoveForward(forwardThrow);
	IntendTurnRight(rightThrow);

	//UE_LOG(LogTemp, Warning , L"%s Vectoring to %s", *tankName, *AIForwardIntention)

}
 