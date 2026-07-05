// Fill out your copyright notice in the Description page of Project Settings.


#include "NarrationWidget.h"
#include "Components/TextBlock.h"

void UNarrationWidget::ShowLine(const FText& Line)
{
	if (NarrationText)
	{
		NarrationText->SetText(Line);
	}
	// Ask the Blueprint to play the fade animation.
	PlayNarrationAnimation();
}
