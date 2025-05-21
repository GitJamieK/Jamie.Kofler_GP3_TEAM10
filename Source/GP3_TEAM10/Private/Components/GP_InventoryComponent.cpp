// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GP_InventoryComponent.h"


// Sets default values for this component's properties
UGP_InventoryComponent::UGP_InventoryComponent()
{
	// Set this component to be initialized when the game starts and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Inventory.Add(EItemType::HealthPack, 0);
	Inventory.Add(EItemType::Key, 0);
	Inventory.Add(EItemType::HandgunAmmo, 0);
	Inventory.Add(EItemType::ShotgunAmmo, 0);
}


// Called when the game starts
void UGP_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGP_InventoryComponent::AddItem(EItemType ItemType, int32 Amount)
{
	if (ItemType == EItemType::None || Amount <= 0) return;

	int32& Count = Inventory.FindOrAdd(ItemType);
	Count += Amount;

	OnInventoryChanged.Broadcast();
}

bool UGP_InventoryComponent::UseItem(EItemType ItemType)
{
	if (!Inventory.Contains(ItemType) || Inventory[ItemType] <= 0) return false;

	Inventory[ItemType]--;

	OnInventoryChanged.Broadcast();
	return true;
}