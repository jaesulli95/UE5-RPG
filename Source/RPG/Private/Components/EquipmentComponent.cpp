// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentComponent.h"
#include "Items/Weapon.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Gear.Add(EEquipmentSlot::EES_Head, NewObject<UEquipment>());
	Gear.Add(EEquipmentSlot::EES_Chest, NewObject<UEquipment>());
	Gear.Add(EEquipmentSlot::EES_Hands, NewObject<UEquipment>());
	Gear.Add(EEquipmentSlot::EES_Legs, NewObject<UEquipment>());
	Gear.Add(EEquipmentSlot::EES_Feet, NewObject<UEquipment>());
	

	//ADD Weapons
	Gear.Add(EEquipmentSlot::EES_MainHand, NewObject<UWeapon>());
}

bool UEquipmentComponent::IsSlotEmpty(EEquipmentSlot SlotToCheck)
{
	if (!Gear.Contains(SlotToCheck)) {
		return false;
	}

	if (Gear[SlotToCheck]->Id == -1) {
		return true;
	}
	return false;
}

UEquipment* UEquipmentComponent::GetEquipmentAtSlot(EEquipmentSlot Slot)
{
	UEquipment* TmpGearSlot = Gear[Slot];
	Gear[Slot] = NewObject<UEquipment>();
	ItemEquipped.Broadcast(Slot, Gear[Slot]);
	return TmpGearSlot;
}

void UEquipmentComponent::EquipGear(UEquipment* GearItem)
{
	EEquipmentSlot EquipSlot = GearItem->EquipSlot;
	Gear[EquipSlot] = GearItem;

	//Broadcast Events
	ItemEquipped.Broadcast(EquipSlot, GearItem);
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

