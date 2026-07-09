// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


AMainMenuGameMode::AMainMenuGameMode()
{
	// We'll set the player controller class later
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Show cursor and set input mode to UI only
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		PC->SetShowMouseCursor(true);
		FInputModeUIOnly InputMode;
		PC->SetInputMode(InputMode);
	}

	// Add the menu widget to the viewport
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
			MainMenuWidget->AddToViewport();
	}
}

