// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Items.h"
#include "Engine/DataTable.h"
#include "CraftingComponent.generated.h"


//THIS ENUM CONTROLS THE STATE OF CRAFTING
UENUM(BlueprintType)
enum class ECraftingStatus : uint8 {
	ECS_Stopped UMETA(DisplayName = "Stopped"),
	ECS_Running UMETA(DisplayName = "Running")
};

UENUM(BlueprintType)
enum class ECraftOpResult : uint8 {
	ECOR_CurrentlyCrafting UMETA(DisplayName = "Aready Crafting"),
	ECOR_MissingMaterials UMETA(DisplayName = "Missing Materials"),
	ECOR_Crafting UMETA(DisplayName="Crafting")
};

USTRUCT(BlueprintType)
struct FItemCraftData : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EItemType Type = EItemType::EIT_Item;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FString Name = "None";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FItemLookup> RequiredItems;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CraftTime = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 QuantityToCraft = 1;

};

USTRUCT(BlueprintType)
struct FCraftRecipe : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FString Name = "None";

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		EItemType Type = EItemType::EIT_Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FItemLookup CraftResult;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FItemLookup> RequiredItems;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CraftTime = 1.f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCraftCompleteDelegate, FItemLookup, CraftItemLookup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCraftUpdateDelegate,ECraftingStatus, Status, float, ElapsedTime, float, TotalTime);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCraftingComponent();
	//Crafting State
	UPROPERTY(BlueprintReadOnly, Category = "Data")
		ECraftingStatus CraftingState = ECraftingStatus::ECS_Stopped;

	UFUNCTION()
		void UpdateCraftTime();

	UFUNCTION(BlueprintCallable)
		virtual ECraftOpResult Craft(UInventoryComponent* Inv, FCraftRecipe RecipeToCraft);

	/*Timers*/
	FTimerHandle CraftTimer;

	/*Events*/
	UPROPERTY(BlueprintAssignable)
		FCraftCompleteDelegate CraftComplete;

	UPROPERTY(BlueprintAssignable)
		FCraftUpdateDelegate CraftUpdate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	FCraftRecipe CurrentCraftRecipe;
	float ElapsedTime = 0.0F;
	float TotalCraftTime = 0.0F;
	float UpdateInterval = 0.01F;
};
