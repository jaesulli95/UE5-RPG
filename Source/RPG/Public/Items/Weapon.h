// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipment.h"
#include "Weapon.generated.h"

/**
 * 
 */

UCLASS()
class RPG_API UWeapon : public UEquipment
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(BlueprintReadOnly)
	FName WeaponSocket;

	virtual void Init(FName ItemLookup, FItemData ItemData, int32 Quantity) override;
	virtual EItemUseResult Use() override;
};
