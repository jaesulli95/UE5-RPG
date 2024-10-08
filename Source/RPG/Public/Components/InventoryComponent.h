// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Items.h"
#include "Components/DataComponent.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemUpdateDelegate, int32, Index, UItems*, Item);


USTRUCT()
struct FItemMetaData {
	GENERATED_BODY()
public:

	TArray<int32> Indexes;
	int32 Total = 0;
	
	void AddItemMetaData(int32 Index, int32 Count) {
		Indexes.Add(Index);
		Total += Count;
	}

	void RemoveIndex(int32 Index, int32 Count) {
		Indexes.Remove(Index);
		Total -= Count;
	}
	
	TArray<int32>& GetIndexes() {
		return Indexes;
	}

	int32 GetNum() {
		return Indexes.Num();
	}
};

USTRUCT()
struct FInventoryMetaData {
	GENERATED_BODY()
public:

	TMap<FName, FItemMetaData> ItemMetaData;

	//CONSTRUCTORS
	FInventoryMetaData() {

	}

	//FUNCTIONS
	void AddItemIndex(FName ItemLookup, int32 Index, const UItems& ItemData) {
		if (!ItemMetaData.Contains(ItemLookup)) {
			ItemMetaData.Add(ItemLookup, FItemMetaData());
		}
		ItemMetaData[ItemLookup].AddItemMetaData(Index, ItemData.CurrentQuantity);
	}


	//TODO:: This is probably the issue right here.
	void RemoveItemIndex(FName ItemLookup, int32 Index, int32 Quantity) {
		if (ItemMetaData.Contains(ItemLookup)) {
			ItemMetaData[ItemLookup].RemoveIndex(Index, Quantity);
			if (ItemMetaData[ItemLookup].GetNum() == 0) {
				ItemMetaData.Remove(ItemLookup);
			}
		}
	}

	bool HasItem(FName ItemLookup) {
		return ItemMetaData.Contains(ItemLookup);
	}

	bool HasItemAtQuantity(FName ItemLookup, int32 Quantity) {
		if (!ItemMetaData.Contains(ItemLookup)) {
			return false;
		}
		return (ItemMetaData[ItemLookup].Total >= Quantity);
	}

	int32 GetNumUnique() {
		TArray<FName> Keys;
		ItemMetaData.GetKeys(Keys);
		return Keys.Num();
	}

	int32 GetItemQuantity(FName ItemLookupId) {
		if (!ItemMetaData.Contains(ItemLookupId)) {
			return 0;
		}
		return ItemMetaData[ItemLookupId].Total;
	}

	TArray<int32> GetItemIndexs(FName ItemLookup) {
		if (!ItemMetaData.Contains(ItemLookup)) {
			return TArray<int32>();
		}

		return ItemMetaData[ItemLookup].GetIndexes();
	}

	void SubFromTotal(FName ItemLookup, int32 Quantity) {
		if (ItemMetaData.Contains(ItemLookup)) {
			ItemMetaData[ItemLookup].Total -= Quantity;
		}
	}

	void AddToTotal(FName ItemLookup, int32 Quantity) {
		if (ItemMetaData.Contains(ItemLookup)) {
			ItemMetaData[ItemLookup].Total += Quantity;
		}
	}

	//DEBUGGING FUNCTIONS
	void DBG_PrintInfo(FName ItemLookup) {
		if (ItemMetaData.Contains(ItemLookup)) {
			UE_LOG(LogTemp, Warning, TEXT("%s--%d--%d"), *ItemLookup.ToString(),
				ItemMetaData[ItemLookup].Total, ItemMetaData[ItemLookup].GetNum());
		}
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Data")
		int32 Size = 100;

	UPROPERTY(BlueprintReadOnly, Category="Data")
		TArray<UItems*> Items;

	UFUNCTION(BlueprintCallable, Category="Inventory-Utilities")
		bool TryAddItem(FItemLookup ItemLookupData);

	UFUNCTION(BlueprintCallable, Category="Inventory-Utilities")
		bool AddItem(class UItems* Item);

	UFUNCTION(BlueprintCallable, Category="Inventory-Utilities")
		void RemoveItem(int32 ItemIndexToRemove);

	UFUNCTION(BlueprintCallable, Category = "Inventory-Utilities")
		void RemoveItemQuantity(int32 ItemIndexToRemove, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category="Inventory-Utilities")
		void Drop(int32 Source, int32 Dest);

	UFUNCTION(BlueprintCallable, Category = "Inventory-Utilities")
		int32 HasItem(int32 Id, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Inventory-Utilities")
		int32 GetItemCount(FName ItemLookupId);

	UFUNCTION()
		void CraftCompleteAddToInventory(FItemLookup ItemLookupId);

	bool HasItemByName(FName ItemLookup, int32 Count);
	void DBG_PrintItemInfo(FName ItemLookup);
	void RemoveItemByNameAndQuantity(FName ItemLookup, int32 Quantity);
	bool GetItemRemovals(FName ItemLookup, int32 Quantity, TArray<FItemRemoval>& ItemRemovals);

	//EVENTS
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FItemUpdateDelegate ItemUpdated;

	//META DATA
	UPROPERTY()
	FInventoryMetaData InventoryMetaData;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TObjectPtr<UDataComponent> DataManager;

	int32 FindOpenSlot();
	void SwapItems(int32 Source, int32 Dest);
	bool StackItem(int32 Source, int32 Dest);
};