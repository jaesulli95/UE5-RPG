// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTags.h"
#include "GameplayTagsModule.h"
#include "Actors/Weapons/WeaponBase.h"
#include "Items.generated.h"

/**
 * 
 */


class UTexture2D;
class UEquipment;
class UArmor;

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8 {
	EES_None UMETA(DisplayName="None"),
	EES_Head UMETA(DisplayName = "Head"),
	EES_Chest UMETA(DisplayName = "Chest"),
	EES_Hands UMETA(DisplayName = "Hands"),
	EES_Legs UMETA(DisplayName = "Legs"),
	EES_Feet UMETA(DisplayName = "Feet"),
	EES_MainHand UMETA(DisplayName = "Main-Hand"),
	EES_Offhand UMETA(DisplayName = "Off-Hand")
};

UENUM(BlueprintType)
enum class EItemType : uint8 {
	EIT_Item UMETA(DisplayName="Item"),
	EIT_Consumable UMETA(DisplayName = "Consumable"),
	EIT_Armor UMETA(DisplayName = "Armor"),
	EIT_Weapon UMETA(DisplayName = "Weapon")
};

USTRUCT()
struct FItemRemoval {
	GENERATED_BODY()
public:
	int32 Index = -1;
	int32 Quantity = -1;

	FItemRemoval() {

	}
	FItemRemoval(int32 _Index, int32 _Quantity) {
		Index = _Index;
		Quantity = _Quantity;
	}
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase {
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Base-Item")
	EItemType ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base-Item")
	TSubclassOf<UItems> ItemClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Base-Item")
	int32 Id = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base-Item")
	FString Name = "None";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base-Item")
	FString Description = "None";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base-Item")
	TSoftObjectPtr<class UTexture2D> IconTexture = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base-Item")
	bool bCanStack = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Base-Item")
	struct FGameplayTag ItemTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Equipment")
	EEquipmentSlot EquipSlot = EEquipmentSlot::EES_None;

	//---------------ARMOR
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Armor")
	bool bHasSkeletalMesh = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Armor")
	TObjectPtr<class USkeletalMesh> Mesh;

	//WEAPON
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FName WeaponAttachSocket;

	FItemData() {

	}
};

//TODO:: GET RID OF THIS
USTRUCT(BlueprintType, Blueprintable)
struct FItemDataQuantity {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FItemData Data;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Quantity = 0;

	FItemDataQuantity() {

	}

	FItemDataQuantity(FItemData _Data, int32 _Quantity) {
		Data = _Data;
		Quantity = _Quantity;
	}
};

USTRUCT(BlueprintType)
struct FItemLookup {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName ItemLookup;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Quantity = 0;
};

UENUM(BlueprintType)
enum class EItemUseResult : uint8 {
	EIUR_DoNothing,
	EIUR_RemoveItem
};


UCLASS(BlueprintType)
class RPG_API UItems : public UObject
{
	GENERATED_BODY()
public:

	UItems();

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	FName ItemLookupName;

	UPROPERTY(BlueprintReadOnly, Category = "Data")
	TSubclassOf<UItems> ItemClass;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	struct FGameplayTag ItemTag;

	UPROPERTY(BlueprintReadOnly, Category="Data")
	int32 Id = -1;

	UPROPERTY(BlueprintReadOnly, Category="Data")
	FString Name = "None";

	UPROPERTY(BlueprintReadOnly, Category="Data")
	FString Description = "None";

	UPROPERTY(BlueprintReadOnly, Category="Data")
	TSoftObjectPtr<class UTexture2D> IconTexture = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Data")
	bool bCanStack = false;

	UPROPERTY(BlueprintReadOnly, Category="Data")
	int32 CurrentQuantity = 1;

	UPROPERTY(BlueprintReadOnly, Category="Data")
	int32 MaxQuantity = 9999; 

	UFUNCTION(BlueprintCallable)
	virtual void Init(FName ItemLookup, FItemData ItemData, int32 Quantity);

	UFUNCTION()
	virtual void SetItemQuantity(int32 Quantity);

	UFUNCTION(BlueprintCallable)
	virtual EItemUseResult Use();
};
