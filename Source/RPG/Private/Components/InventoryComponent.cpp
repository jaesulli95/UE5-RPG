// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InventoryMetaData = FInventoryMetaData();
}
bool UInventoryComponent::TryAddItem(FItemLookup ItemLookupData)
{
	FItemData ItemData = FItemData();
	if (DataManager) {
		if (DataManager->GetItemData(ItemLookupData.ItemLookup, ItemData)) {
			UItems* NewItem = NewObject<UItems>(this, ItemData.ItemClass);
			NewItem->Init(ItemLookupData.ItemLookup, ItemData, ItemLookupData.Quantity);
			return AddItem(NewItem);
		}
		return false;
	}
	return false;
}
bool UInventoryComponent::AddItem(UItems* Item)
{
	int32 Location = FindOpenSlot();
	if (Location == -1) {
		return false;
	}
	Items[Location] = Item;
	ItemUpdated.Broadcast(Location, Item);

	InventoryMetaData.AddItemIndex(Item->ItemLookupName, Location, *Items[Location]);
	return true;
}
void UInventoryComponent::RemoveItem(int32 ItemIndexToRemove)
{
	FName ItemLookup = Items[ItemIndexToRemove]->ItemLookupName;
	int32 Quantity = Items[ItemIndexToRemove]->CurrentQuantity;
	Items[ItemIndexToRemove] = NewObject<UItems>();
	ItemUpdated.Broadcast(ItemIndexToRemove, Items[ItemIndexToRemove]);
	InventoryMetaData.RemoveItemIndex(ItemLookup,ItemIndexToRemove, Quantity);
}
void UInventoryComponent::RemoveItemQuantity(int32 ItemIndexToRemove, int32 Quantity)
{
	if (Items[ItemIndexToRemove]->CurrentQuantity == Quantity) {
		RemoveItem(ItemIndexToRemove);
		return;
	}

	Items[ItemIndexToRemove]->CurrentQuantity -= Quantity;
	ItemUpdated.Broadcast(ItemIndexToRemove, Items[ItemIndexToRemove]);
	InventoryMetaData.SubFromTotal(Items[ItemIndexToRemove]->ItemLookupName, Quantity);
	return;
}
void UInventoryComponent::RemoveItemByNameAndQuantity(FName ItemLookup, int32 Quantity)
{
	TArray<FItemRemoval> Removals;
	if (GetItemRemovals(ItemLookup, Quantity, Removals)) {
		for (int32 i = 0; i < Removals.Num(); i++) {
			UE_LOG(LogTemp, Warning, TEXT("Item Lookup Name: %s -- Quantity: %d"), *ItemLookup.ToString(), Removals[i].Quantity);
			RemoveItemQuantity(Removals[i].Index, Removals[i].Quantity);
		}
	}
}
bool UInventoryComponent::GetItemRemovals(FName ItemLookup, int32 Quantity, TArray<FItemRemoval>& ItemRemovals) {
	int32 TotalRemaining = Quantity;
	TArray<int32> ItemIndexes = InventoryMetaData.GetItemIndexs(ItemLookup);
	for (int32 i = 0; i < ItemIndexes.Num(); i++) {
		int32 Index = ItemIndexes[i];
		int32 Count = Items[Index]->CurrentQuantity;

		//TODO: Series of IF Statements
		if (Count < TotalRemaining) {
			ItemRemovals.Add(FItemRemoval(Index, Count));
			TotalRemaining -= Quantity;
		}
		else  if (Count >= TotalRemaining) {
			ItemRemovals.Add(FItemRemoval(Index, TotalRemaining));
			TotalRemaining = 0;
		}

		if (TotalRemaining == 0) {
			return true;
		}
	}
	return true;
}
void UInventoryComponent::SwapItems(int32 Source, int32 Dest)
{

	//Just Need to do the Swap function here for Inventory Meta Data;
	UItems* TmpItem = Items[Source];
	Items[Source] = Items[Dest];
	Items[Dest] = TmpItem;
}
bool UInventoryComponent::StackItem(int32 Source, int32 Dest)
{
	if (!Items[Source]->bCanStack) {
		return false;
	}
	int32 QuantityTotal = Items[Source]->CurrentQuantity + Items[Dest]->CurrentQuantity;
	if (QuantityTotal < Items[Dest]->MaxQuantity) {
		Items[Dest]->CurrentQuantity += Items[Source]->CurrentQuantity;
		RemoveItem(Source);
		ItemUpdated.Broadcast(Dest, Items[Dest]);
		return true;
	}
	return false;
}
void UInventoryComponent::Drop(int32 Source, int32 Dest)
{
	if (Items[Source]->Id == Items[Dest]->Id) {
		//Add Items to count
		if (!StackItem(Source, Dest)) {
			SwapItems(Source, Dest);
		}
	}
	else {
		SwapItems(Source, Dest);
	}

	ItemUpdated.Broadcast(Source, Items[Source]);
	ItemUpdated.Broadcast(Dest, Items[Dest]);
}
int32 UInventoryComponent::HasItem(int32 Id, int32 Count)
{
	for (int32 i = 0; i < Size; i++) {
		if (Items[i]->Id && Items[i]->CurrentQuantity >= Count) {
			return i;
		}
	}
	return -1;
}
int32 UInventoryComponent::GetItemCount(FName ItemLookupId)
{
	return InventoryMetaData.GetItemQuantity(ItemLookupId);
}
void UInventoryComponent::CraftCompleteAddToInventory(FItemLookup ItemLookupData)
{
	TryAddItem(ItemLookupData);
}
bool UInventoryComponent::HasItemByName(FName ItemLookup, int32 Count)
{
	return InventoryMetaData.HasItemAtQuantity(ItemLookup, Count);

}
void UInventoryComponent::DBG_PrintItemInfo(FName ItemLookup)
{
	InventoryMetaData.DBG_PrintInfo(ItemLookup);
}
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Items.Init(NewObject<UItems>(), Size);

	AGameStateBase* _GameState = UGameplayStatics::GetGameState(GetWorld());
	DataManager = _GameState->FindComponentByClass<UDataComponent>();
}
int32 UInventoryComponent::FindOpenSlot() {
	for (int32 i = 0; i < Size; i++) {
		if (Items[i]->Id == -1) {
			return i;
		}
	}
	return -1; //Inventory Full
}