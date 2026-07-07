#include "MainHud.h"
#include "Blueprint/UserWidget.h"

void AMainHud::BeginPlay()
{
	Super::BeginPlay();
	ShowMainMenu();
	ShowInventory();
}

UUserWidget* AMainHud::CreateOrGetWidget(TObjectPtr<UUserWidget>& Widget, TSubclassOf<UUserWidget> WidgetClass)
{
	if (!Widget && WidgetClass)
	{
		Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	}
	return Widget;
}

void AMainHud::HideAllWidgets()
{
	if (MainMenuWidget)  MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	if (PauseMenuWidget) PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	if (InventoryWidget) InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMainHud::ShowMainMenu()
{
	HideAllWidgets();
	UUserWidget* Widget = CreateOrGetWidget(MainMenuWidget, MainMenuWidgetClass);
	if (Widget)
	{
		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainHud::ShowPauseMenu()
{
	HideAllWidgets();
	UUserWidget* Widget = CreateOrGetWidget(PauseMenuWidget, PauseMenuWidgetClass);
	if (Widget)
	{
		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainHud::ShowInventory()
{
	HideAllWidgets();
	UUserWidget* Widget = CreateOrGetWidget(InventoryWidget, InventoryWidgetClass);
	if (Widget)
	{
		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
}