// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AimingComponent.generated.h"

//Forward Declaration
class UTankBarrel;	
class UTankTurret;
class AProjectile;

UENUM(BlueprintType)
enum class EFiringState :uint8 {
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK2_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector hitLocation);



	UFUNCTION(BlueprintCallable, Category = Fire)
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable)
	int32 GetRoundLeft() const;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* turret = nullptr;
	void MoveBarrelToward(FVector aimDirection);

	UFUNCTION(BlueprintCallable, Category ="Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//TODO remove once firing is moved to aiming component
	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 10000;	// 1000 m/s
	
	FVector AimDirection;



	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> projectileBlueprint;

	double lastReloadTime;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadInterval = 2;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 roundLeft = 3;

	bool IsBarrelMoving();
	

};
