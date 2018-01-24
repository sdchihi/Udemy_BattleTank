// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK2_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Launch(float speed);

private:
	UProjectileMovementComponent* projectileComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* launchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* impactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* explosionForce = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	void OnTimerExpire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float destroyDelay = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float projectileDamage = 10;


};
