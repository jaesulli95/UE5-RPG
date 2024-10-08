// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Items/Items.h"
#include "Actors/Weapons/WeaponBase.h"
#include "RPGCharacter.generated.h"


class UInventoryComponent;
class UEquipmentComponent;
class UCraftingComponent;

USTRUCT(BlueprintType)
struct FSKMData {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> SKMesh;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> DefaultSkeletalMesh;
};

UCLASS(config=Game)
class ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	ARPGCharacter();
	
	UPROPERTY(BlueprintReadWrite)
		bool bAxeEquipped = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Components")
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")
	TObjectPtr<UCraftingComponent> CraftingComponent;

	//Armor For Character -- Would put this in a MeshManager Class if more productive3
	UPROPERTY(BlueprintReadOnly)
	TMap<EEquipmentSlot, FSKMData> MeshMap;

	UFUNCTION(BlueprintCallable)
	void SetGearMesh(EEquipmentSlot Slot, USkeletalMesh* GearMesh);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Utility")
	USkeletalMesh* GetDefaultMesh(EEquipmentSlot Slot);

	//Weapon for Character
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AWeaponBase> Weapon;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EquipWeapon(TSubclassOf<AWeaponBase> WeaponClass, FName WeaponSocket);

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable)
	void AddSKMToMap(EEquipmentSlot Slot, FSKMData SKMData);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

