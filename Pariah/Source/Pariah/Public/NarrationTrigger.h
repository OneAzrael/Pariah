// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NarrationTrigger.generated.h"

class UBoxComponent;

UCLASS()
class PARIAH_API ANarrationTrigger : public AActor
{
	GENERATED_BODY()

public:
	ANarrationTrigger();

protected:
	virtual void BeginPlay() override;

	// The invisible box the player walks into.
	UPROPERTY(VisibleAnywhere, Category="Narration")
	TObjectPtr<UBoxComponent> TriggerBox;

	// The line this trigger shows. Set per-placed-trigger in the editor.
	UPROPERTY(EditAnywhere, Category="Narration")
	FText NarrationLine;

	// If true, only fires the first time the player enters.
	UPROPERTY(EditAnywhere, Category="Narration")
	bool bFireOnce = true;

	bool bHasFired = false;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};