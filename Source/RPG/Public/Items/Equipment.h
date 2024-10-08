// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Items.h"
#include "Equipment.generated.h"

/**
 * 
 */

UCLASS(ABSTRACT)
class RPG_API UEquipment : public UItems
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="Data")
	EEquipmentSlot EquipSlot = EEquipmentSlot::EES_Chest;

	virtual void Init(FName ItemLookup, FItemData ItemData, int32 Quantity) override;
	virtual void SetItemQuantity(int32 Quantity);
	virtual EItemUseResult Use() override;
};
