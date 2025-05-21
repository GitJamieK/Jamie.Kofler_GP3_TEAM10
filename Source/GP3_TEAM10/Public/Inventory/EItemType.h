// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None              UMETA(DisplayName = "None"),
	HealthPack        UMETA(DisplayName = "Health Pack"),
	Key               UMETA(DisplayName = "Key"),
	HandgunAmmo       UMETA(DisplayName = "Handgun Ammo"),
	ShotgunAmmo		  UMETA(DisplayName = "Shotgun Ammo"),
};