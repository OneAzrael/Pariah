#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::TryAddItem(FName ItemID, int32 Quantity, bool bIsStackable)
{
	if (ItemID.IsNone() || Quantity <= 0) return false;
	
	int32 Index = FindSlotIndex(ItemID);
	if (Index != INDEX_NONE)
	{
		if (!Slots[Index].bIsStackable) return false; // same item exists but not stackable
		Slots[Index].Quantity += Quantity;
		OnInventoryChanged.Broadcast();
		return true;
	}
	
	if (Slots.Num() >= MaxSlots) return false;

        FInventorySlot& NewSlot = Slots.AddDefaulted_GetRef();
		NewSlot.ItemId = ItemID;
		NewSlot.Quantity = Quantity;
		NewSlot.bIsStackable = bIsStackable; // missing this

	
	OnInventoryChanged.Broadcast();
	return true;
}

bool UInventoryComponent::TryRemoveItem(FName ItemID, int32 Quantity)
{
	if (ItemID.IsNone() || Quantity <= 0) return false;

	int32 Index = FindSlotIndex(ItemID);
	if (Index == INDEX_NONE) return false;
	if (Slots[Index].Quantity < Quantity) return false;

	Slots[Index].Quantity -= Quantity;
	if (Slots[Index].Quantity == 0)
		Slots.RemoveAt(Index);

	OnInventoryChanged.Broadcast();
	return true;
}

bool UInventoryComponent::HasItem(FName ItemID, int32 Quantity) const
{
	// First we find the name of the id
	// If it doesnt exist we exit
	// If true we show the ammount
	int32 Index = FindSlotIndex(ItemID);
	if (Index == INDEX_NONE) return false;
	return Slots[Index].Quantity >= Quantity;
}

int32 UInventoryComponent::FindSlotIndex(FName ItemID) const
{
	//Simple for loop
	for (int32 i = 0; i < Slots.Num(); ++i)
	{
		if (Slots[i].ItemId == ItemID)
			return i;
	}
	return INDEX_NONE;
}

void UInventoryComponent::DebugPrintInventory()
{
	
	// Shows Item id first then the ammount
	// 1 x 2
	// ItemID 1, Quanitiy 2 happens only on pickup
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("=== INVENTORY ==="));
	for (const FInventorySlot& Slot : Slots)
	{
		FString Line = Slot.ItemId.ToString() + FString::Printf(TEXT(" x%d"), Slot.Quantity);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Line);
	}
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	OnInventoryChanged.AddDynamic(this, &UInventoryComponent::DebugPrintInventory);
}
