// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableBase.h"

#include "InventoryComponent.generated.h"



// We use struct because it is more optimised than putting it in class

// We use ItemID to find add/remove items 
USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FName ItemId;
	
	UPROPERTY(BlueprintReadOnly)
	int32 Quantity = 0;

	UPROPERTY(BlueprintReadOnly)
	bool bIsStackable = false;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTexture2D> ItemIcon;
};

// Delegate
// Declare - We define a new  delate
// Dynamic - can be used in bp / c++
// Multicast - Multiple things can listen to it. (UI, HUD, Interaction etc)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent))
class PARIAH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	 UInventoryComponent();
	void BeginPlay() override;
	
	// Just setting basic variables
	
	// In rider press F12 on a  class name like "TryAddItem" to find where its being used
	
	// Try to add an item where interactable is looking at
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryAddItem(FName ItemID, int32 Quantity = 1, bool bIsStackable = false, UTexture2D* Icon = nullptr); 
	
	// Same concept just removing an item
	// Call this function when you want to destory an item
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryRemoveItem(FName ItemID, int32 Quantity = 1); 
	
	
	// Call this function to see if a player has a specifc item 
	// used for keycard/keys and such
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(FName ItemID, int32 Quantity = 1) const;
	
	// Nothing here yet
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const TArray<FInventorySlot>& Getslots() const { return Slots; }
	
	// Max slot. Example = [Keycard] [KeyDoor] [KeyBasement]
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	int32 MaxSlots = 3;
	
	// This is what you will call if you want to change stuff :)
	// Include these at your actor cpp
    //#include "InventoryComponent.h"
	//	UInventoryComponent* Inventory = FindComponentByClass<UInventoryComponent>();
	//  if (Inventory)
	//	Inventory -> TryAddItem("Item_Cube", 1, true);
	//  ^ This is an example
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;
	
private:
	UPROPERTY()
	TArray<FInventorySlot> Slots;

	int32 FindSlotIndex(FName ItemID) const;
	
	UFUNCTION()
	void DebugPrintInventory();
};