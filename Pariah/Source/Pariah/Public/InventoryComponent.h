// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


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
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent))
class PARIAH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	 UInventoryComponent();
	void BeginPlay() override;
	
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryAddItem(FName ItemID, int32 Quantity = 1, bool bIsStackable = false); 
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryRemoveItem(FName ItemID, int32 Quantity = 1); 
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(FName ItemID, int32 Quantity = 1) const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	const TArray<FInventorySlot>& Getslots() const { return Slots; }
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	int32 MaxSlots = 3;
	
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;
	
private:
	UPROPERTY()
	TArray<FInventorySlot> Slots;

	int32 FindSlotIndex(FName ItemID) const;
	
	UFUNCTION()
	void DebugPrintInventory();
};