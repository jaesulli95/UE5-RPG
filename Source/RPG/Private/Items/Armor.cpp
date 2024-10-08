// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Armor.h"
#include "Kismet/GameplayStatics.h"
#include "RPG/RPGCharacter.h"
#include "Components/EquipmentComponent.h"
#include "Components/InventoryComponent.h"

void UArmor::Init(FName ItemLookup, FItemData ItemData, int32 Quantity)
{
	Super::Init(ItemLookup, ItemData, 1);
	bHasSkeletalMesh = ItemData.bHasSkeletalMesh;
	Mesh = ItemData.Mesh;
}

EItemUseResult UArmor::Use()
{
	ARPGCharacter* Character = Cast<ARPGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character) {
		UEquipmentComponent* Gear = Character->EquipmentComponent;
		if (Gear) {
			if (!Gear->IsSlotEmpty(EquipSlot)) {
				UItems* ReturnedGearSlot = Gear->GetEquipmentAtSlot(EquipSlot);
				//ADD this too the inventory system
				Character->InventoryComponent->AddItem(ReturnedGearSlot);
			}
			Gear->EquipGear(this);
			//Character Set Skeletal Mesh Here
			if (bHasSkeletalMesh) {
				Character->SetGearMesh(EquipSlot, Mesh);
			}
			return EItemUseResult::EIUR_RemoveItem;
		}
	}
	return EItemUseResult::EIUR_DoNothing;
}
