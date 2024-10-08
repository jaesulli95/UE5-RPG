// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "RPG/RPGCharacter.h"
#include "Components/EquipmentComponent.h"
#include "Components/InventoryComponent.h"

void UWeapon::Init(FName ItemLookup, FItemData ItemData, int32 Quantity)
{
	Super::Init(ItemLookup, ItemData, Quantity);
	//TODO:: Implement the rest of the code here.
	WeaponClass = ItemData.WeaponClass;
	WeaponSocket = ItemData.WeaponAttachSocket;
}

EItemUseResult UWeapon::Use() {

	ARPGCharacter* Character = Cast<ARPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character) {
		UEquipmentComponent* Gear = Character->EquipmentComponent;
		if (Gear) {
			if (!Gear->IsSlotEmpty(EquipSlot)) {
				UItems* ReturnedGearSlot = Gear->GetEquipmentAtSlot(EquipSlot);
				Character->InventoryComponent->AddItem(ReturnedGearSlot);
			}
			Gear->EquipGear(this);
			Character->EquipWeapon(WeaponClass, WeaponSocket);
			return EItemUseResult::EIUR_RemoveItem; //Remove the Item from the Inventory;
		}
	}
	return EItemUseResult::EIUR_DoNothing;
}