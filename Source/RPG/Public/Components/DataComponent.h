// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Items/Items.h"
#include "DataComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDataComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Data-Tables")
		TObjectPtr<UDataTable> ItemsTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data-Tables")
		TObjectPtr<UDataTable> CraftingRecipes;

	bool GetItemData(FName ItemLookup, FItemData& ResultItemData);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
