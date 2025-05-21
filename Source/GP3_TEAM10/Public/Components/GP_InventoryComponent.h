// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/EItemType.h"
#include "GP_InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP3_TEAM10_API UGP_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGP_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly)
	TMap<EItemType, int32> Inventory;

	UFUNCTION(BlueprintCallable)
	void AddItem(EItemType ItemType, int32 Amount = 1);
	
	UFUNCTION(BlueprintCallable)
	bool UseItem(EItemType ItemType);

	UFUNCTION(BlueprintCallable)
	int32 GetItemAmount(EItemType ItemType) const
	{
		if (Inventory[ItemType] <= 0 || !Inventory.Contains(ItemType)) return 0;
		else return Inventory[ItemType];
	};

	UFUNCTION(BlueprintCallable)
	bool HasItem(EItemType ItemType) const
	{
		if (Inventory.Contains(ItemType)) return true;
		else return false;
	};

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;
};
