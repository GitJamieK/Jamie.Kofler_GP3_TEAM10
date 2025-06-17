// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None              UMETA(DisplayName = "None"),
	HealthPack        UMETA(DisplayName = "Health Pack"),

	
	KeyTEMP			  UMETA(DisplayName = "KeyTEMP"), // can be removed
	
	key1			  UMETA(DisplayName = "Key1"),
	key2			  UMETA(DisplayName = "Key2"),
	key3			  UMETA(DisplayName = "Key3"),
	
	HandgunAmmo       UMETA(DisplayName = "Handgun Ammo"),
	ShotgunAmmo		  UMETA(DisplayName = "Shotgun Ammo"),
};