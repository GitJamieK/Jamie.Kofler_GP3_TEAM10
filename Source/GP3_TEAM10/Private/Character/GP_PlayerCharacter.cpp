// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GP_PlayerCharacter.h"

AGP_PlayerCharacter::AGP_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGP_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGP_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

