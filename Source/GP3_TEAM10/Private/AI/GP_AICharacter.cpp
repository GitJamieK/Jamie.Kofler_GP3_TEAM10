// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GP_AICharacter.h"
#include "AI/GP_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AGP_AICharacter::AGP_AICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; //PlacedInWorldOrSpawned  Disabled
	AIControllerClass = AGP_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
}

void AGP_AICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGP_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_AICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

