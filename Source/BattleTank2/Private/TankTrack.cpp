// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
	
}


void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit );
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewayForce();
	currentThrottle = 0;
}

// Called every frame
 void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction);
}

 void UTankTrack::ApplySidewayForce()
 {
	 // �̲����� �ӵ�
	 auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());	// GetComponentVelocity ��ǻ� Owner �� �װͰ� ����.
	 auto DeltaTime = GetWorld()->GetDeltaSeconds();
	 auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();

	 auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	 auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;	// Ʈ���� 2���� 2�� ���� 

	 tankRoot->AddForce(correctionForce);
 }


void UTankTrack::SetThrottle(float throttle) {

	currentThrottle = FMath::Clamp < float > (currentThrottle + throttle, -1, 1);
	
}

void UTankTrack::DriveTrack() {
	auto forceApllied = GetForwardVector() * currentThrottle * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();

	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApllied, forceLocation);
}