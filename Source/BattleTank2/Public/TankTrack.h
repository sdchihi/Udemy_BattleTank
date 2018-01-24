// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK2_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
	
public:
	UFUNCTION(BlueprintCallable, Category= Input)
	void SetThrottle(float throttle);

	//Max force per track
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // 40톤(40,000kg)짜리 탱크라고 가정했을때, 1g 가속력


private :
	UTankTrack();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	void ApplySidewayForce();

	void DriveTrack();

	float currentThrottle = 0;
};
