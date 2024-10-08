// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Equipment.h"
#include "Armor.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UArmor : public UEquipment
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category="Data")
	bool bHasSkeletalMesh = false;

	UPROPERTY(BlueprintReadOnly, Category="Data")
	FName MeshNameIndex = "None";

	UPROPERTY(BlueprintReadOnly, Category="Data")
	TObjectPtr<class USkeletalMesh> Mesh;

	virtual void Init(FName ItemLookup, FItemData ItemData, int32 Quantity) override;
	virtual EItemUseResult Use() override;
};
