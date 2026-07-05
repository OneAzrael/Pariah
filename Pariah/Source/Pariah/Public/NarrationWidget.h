// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NarrationWidget.generated.h"

class UTextBlock;

UCLASS()
class PARIAH_API UNarrationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Call this from C++ to show a line of narration text.
	UFUNCTION(BlueprintCallable, Category="Narration")
	void ShowLine(const FText& Line);

protected:
	// The text element in the Blueprint. Name must match exactly: NarrationText.
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NarrationText;

	// Implemented in Blueprint: plays the fade in/hold/fade out animation.
	UFUNCTION(BlueprintImplementableEvent, Category="Narration")
	void PlayNarrationAnimation();
};
