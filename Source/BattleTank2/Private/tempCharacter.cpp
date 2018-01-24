// Fill out your copyright notice in the Description page of Project Settings.

#include "tempCharacter.h"


// Sets default values
AtempCharacter::AtempCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AtempCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AtempCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AtempCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

