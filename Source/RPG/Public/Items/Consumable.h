// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Items.h"
#include "Consumable.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UConsumable : public UItems
{
	GENERATED_BODY()
public:
	UConsumable();
	virtual void Init(FName ItemLookup, FItemData ItemData, int32 Quantity) override;
	virtual void SetItemQuantity(int32 Quantity);
	virtual EItemUseResult Use() override;
};
