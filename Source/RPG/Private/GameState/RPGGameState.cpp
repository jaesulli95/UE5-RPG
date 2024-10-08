// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/RPGGameState.h"
#include "Components/DataComponent.h"

ARPGGameState::ARPGGameState()
{
	DataManager = CreateDefaultSubobject<UDataComponent>("DataManager");
}

bool ARPGGameState::GetItemData(FName ItemLookup, FItemData& ResultItemData)
{
	if (DataManager) {
		return DataManager->GetItemData(ItemLookup, ResultItemData);
	}
	return false;
}
