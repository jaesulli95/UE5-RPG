// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Equipment.h"

void UEquipment::Init(FName ItemLookup, FItemData ItemData, int32 Quantity)
{
	Super::Init(ItemLookup, ItemData, 1);
	EquipSlot = ItemData.EquipSlot;
	MaxQuantity = 1;
}

void UEquipment::SetItemQuantity(int32 Quantity)
{
	CurrentQuantity = 1;
}

EItemUseResult UEquipment::Use()
{
	return EItemUseResult::EIUR_DoNothing;
}
