// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

#include "InventoryComponent.h"

UInteractableBase::UInteractableBase()
{
	PrimaryComponentTick.bCanEverTick = false; // no per-frame work needed
}

void UInteractableBase::Interact(AActor* Interactor)
{
	if (!bIsEnabled)        return;   // turned off
	if (!CanInteract())     return;   // condition not met (e.g. door locked)
	
	OnInteract.Broadcast(Interactor); // notify BP / other listeners
	HandleInteract(Interactor);       // type-specific C++ behaviour

}

bool UInteractableBase::CanInteract_Implementation() const
{
	return bIsEnabled;
}

void UInteractableBase::HandleInteract(AActor* Interactor)
{
	if (bIsPickup)
	{
		
		UInventoryComponent* Inventory = Interactor->FindComponentByClass<UInventoryComponent>();
		if (Inventory && Inventory->TryAddItem(ItemID, Quantity, bIsStackable, ItemIcon))
		{
			GetOwner()->Destroy();
		}
	}
}