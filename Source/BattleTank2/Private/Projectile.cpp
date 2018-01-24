// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/PhysicsEngine/RadialForceComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Classes/GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Component"));
	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false);

	//todo
	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->bAutoActivate = false;
	
	projectileComponent->bAutoActivate = false;



	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Launch(float speed)
{
	projectileComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileComponent->Activate();

}



void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
	launchBlast->Deactivate();
	impactBlast->Activate();
	explosionForce->FireImpulse();

	SetRootComponent(impactBlast);
	collisionMesh->DestroyComponent();
	
	UGameplayStatics::ApplyRadialDamage(
		this,
		projectileDamage,
		GetActorLocation(),
		explosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, destroyDelay, false);
}


void AProjectile::OnTimerExpire() {

	Destroy();
}