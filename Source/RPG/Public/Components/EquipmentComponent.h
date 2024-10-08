// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Items.h"
#include "Items/Equipment.h"
#include "EquipmentComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemEquipped, EEquipmentSlot, Slot, UEquipment*, GearItem);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	TMap<EEquipmentSlot, UEquipment*> Gear;

	UFUNCTION(BlueprintCallable)
	bool IsSlotEmpty(EEquipmentSlot SlotToCheck);

	UFUNCTION(BlueprintCallable)
	UEquipment* GetEquipmentAtSlot(EEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable)
	void EquipGear(UEquipment* GearItem);

	//Event Delegates
	UPROPERTY(BlueprintAssignable)
	FItemEquipped ItemEquipped;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;		
};
