// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableBase.generated.h"

// Multicast + Blueprint-bindable event, passing the actor that interacted.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, AActor*, Interactor);

UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class PARIAH_API UInteractableBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableBase();

	// The player calls this when they interact with this component's owner.
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Interact(AActor* Interactor);

	// Whether this can be interacted with right now. Override in C++ or BP.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	bool CanInteract() const;
	virtual bool CanInteract_Implementation() const;

	// Text the HUD shows ("Open Door", "Pick Up Key").
	UFUNCTION(BlueprintCallable, Category="Interaction")
	FText GetInteractPrompt() const { return InteractPrompt; }

	// Fires on a valid interaction. C++ and BP can both listen.
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FOnInteract OnInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	FText InteractPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	bool bIsEnabled = true;

protected:
	// Subclass-specific. Base does nothing; subclasses override.
	virtual void HandleInteract(AActor* Interactor);
};