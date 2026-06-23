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

	HandleInteract(Interactor);       // type-specific C++ behaviour
	OnInteract.Broadcast(Interactor); // notify BP / other listeners
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
		if (Inventory && Inventory->TryAddItem(ItemID, Quantity, bIsStackable))
		{
			GetOwner()->Destroy();
		}
	}
}