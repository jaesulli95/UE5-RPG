// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Consumable.h"

UConsumable::UConsumable() {

}
void UConsumable::Init(FName ItemLookup, FItemData ItemData, int32 Quantity)
{
	Super::Init(ItemLookup, ItemData, Quantity);
}

void UConsumable::SetItemQuantity(int32 Quantity)
{
	CurrentQuantity = Quantity;
}

EItemUseResult UConsumable::Use()
{
	//Do some kind of affect here 
	CurrentQuantity -= 1;

	if (CurrentQuantity == 0) {
		return EItemUseResult::EIUR_RemoveItem;
	}
	return EItemUseResult::EIUR_DoNothing;
}
