// Fill out your copyright notice in the Description page of Project Settings.
#include "Items/Items.h"
#include "Items/Armor.h"

UItems::UItems() {
	Id = -1;
}

void UItems::Init(FName ItemLookup, FItemData ItemData, int32 Quantity)
{
	//Set the Data here.
	ItemClass = ItemData.ItemClass;
	ItemTag = ItemData.ItemTag;
	Id = ItemData.Id;
	Name = ItemData.Name;
	Description = ItemData.Description;
	IconTexture = ItemData.IconTexture;
	bCanStack = ItemData.bCanStack;
	ItemLookupName = ItemLookup;

	SetItemQuantity(Quantity);

}

void UItems::SetItemQuantity(int32 Quantity)
{
	CurrentQuantity = Quantity;
}

EItemUseResult UItems::Use()
{
	UE_LOG(LogTemp, Warning, TEXT("Using a Regular Item"));
	return EItemUseResult::EIUR_DoNothing;
}
