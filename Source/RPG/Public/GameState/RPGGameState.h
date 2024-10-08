// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RPGGameState.generated.h"

/**
 * 
 */

class UDataComponent;

UCLASS()
class RPG_API ARPGGameState : public AGameState
{
	GENERATED_BODY()
public:
	ARPGGameState();

	UFUNCTION()
	bool GetItemData(FName ItemLookup, FItemData& ResultItemData);
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
		TObjectPtr<UDataComponent> DataManager;
};
