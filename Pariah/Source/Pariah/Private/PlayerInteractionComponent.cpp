// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractionComponent.h"
#include "InteractableBase.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true; // we trace every frame
}

void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Grab the owner's camera to trace from. We don't care that the owner
	// is AMainCharacter specifically -- only that it has a camera.
	if (AActor* MyOwner = GetOwner())
	{
		ViewCamera = MyOwner->FindComponentByClass<UCameraComponent>();
	}
}

void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateFocusedInteractable();
}

void UPlayerInteractionComponent::UpdateFocusedInteractable()
{
	FocusedInteractable = nullptr;
	if (!ViewCamera) return;

	const FVector Start = ViewCamera->GetComponentLocation();
	const FVector End   = Start + ViewCamera->GetForwardVector() * InteractRange;

	if (bDrawDebugLine)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, -1.0f, 0, 1.0f);
	}

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			// The bridge between the two halves: does the thing I hit
			// carry an interactable component?
			FocusedInteractable = HitActor->FindComponentByClass<UInteractableBase>();
		}
	}
}

void UPlayerInteractionComponent::TryInteract()
{
	if (FocusedInteractable && FocusedInteractable->bIsEnabled)
	{
		FocusedInteractable->Interact(GetOwner());
	}
}

