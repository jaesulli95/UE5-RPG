// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CraftingComponent.h"
#include "Components/InventoryComponent.h"

// Sets default values for this component's properties
UCraftingComponent::UCraftingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UCraftingComponent::UpdateCraftTime()
{
	ElapsedTime += UpdateInterval;
	if (ElapsedTime > TotalCraftTime) {
		GetWorld()->GetTimerManager().PauseTimer(CraftTimer);
		CraftComplete.Broadcast(CurrentCraftRecipe.CraftResult);
		CraftingState = ECraftingStatus::ECS_Stopped;
	}

	CraftUpdate.Broadcast(CraftingState, ElapsedTime, CurrentCraftRecipe.CraftTime);
}

ECraftOpResult UCraftingComponent::Craft(UInventoryComponent* Inv, FCraftRecipe RecipeToCraft) {

	if (CraftingState == ECraftingStatus::ECS_Running) {
		//Currently Crafting so return!
		return ECraftOpResult::ECOR_CurrentlyCrafting;
	}

	CurrentCraftRecipe = RecipeToCraft;

	int32 ReqdItemsNum = RecipeToCraft.RequiredItems.Num();
	TArray<FItemLookup> ReqItems = CurrentCraftRecipe.RequiredItems;
	
	//Check too see if we have the supplies for the Craft
	for (int32 i = 0; i < ReqdItemsNum; i++) {
		if (!Inv->HasItemByName(ReqItems[i].ItemLookup, ReqItems[i].Quantity)) {
			//Inv->DBG_PrintItemInfo(ReqItems[i].ItemLookup);
			return ECraftOpResult::ECOR_MissingMaterials;
		}
	}

	for (int32 i = 0; i < ReqdItemsNum; i++) {
		Inv->RemoveItemByNameAndQuantity(ReqItems[i].ItemLookup, ReqItems[i].Quantity);
	}

	ElapsedTime = 0.0F;
	TotalCraftTime = CurrentCraftRecipe.CraftTime;
	CraftingState = ECraftingStatus::ECS_Running;
	GetWorld()->GetTimerManager().UnPauseTimer(CraftTimer);
	return ECraftOpResult::ECOR_Crafting;
}

// Called when the game starts
void UCraftingComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(CraftTimer, this, &UCraftingComponent::UpdateCraftTime, UpdateInterval, true, 0.0f);
	GetWorld()->GetTimerManager().PauseTimer(CraftTimer);
}