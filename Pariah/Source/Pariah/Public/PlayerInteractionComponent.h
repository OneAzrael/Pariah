// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"

class UInteractableBase;
class UCameraComponent;

UCLASS(ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent))
class PARIAH_API UPlayerInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPlayerInteractionComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    // Called from the character's Interact input binding.
    UFUNCTION(BlueprintCallable, Category="Interaction")
    void TryInteract();

    // What the player is currently looking at (or null).
    UFUNCTION(BlueprintCallable, Category="Interaction")
    UInteractableBase* GetFocusedInteractable() const { return FocusedInteractable; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category="Interaction")
    float InteractRange = 250.0f;

    UPROPERTY(EditAnywhere, Category="Interaction")
    bool bDrawDebugLine = false;

private:
    UPROPERTY()
    TObjectPtr<UCameraComponent> ViewCamera;

    UPROPERTY()
    TObjectPtr<UInteractableBase> FocusedInteractable;

    void UpdateFocusedInteractable();
};