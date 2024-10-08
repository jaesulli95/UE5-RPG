// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DataComponent.h"

// Sets default values for this component's properties
UDataComponent::UDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


bool UDataComponent::GetItemData(FName ItemLookup, FItemData& ResultItemData)
{
	if (ItemsTable) {
		FItemData* ItemData = ItemsTable->FindRow<FItemData>(ItemLookup, "");
		if (ItemData) {
			ResultItemData = *ItemData;
			return true;
		}
		return false;
	}
	return false;
}

// Called when the game starts
void UDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

