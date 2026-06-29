// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHud.generated.h"

/**
 * 
 */
UCLASS()
class PARIAH_API AMainHud : public AHUD
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category="HUD")
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable, Category="HUD")
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable, Category="HUD")
	void ShowInventory();

	UFUNCTION(BlueprintCallable, Category="HUD")
	void HideAllWidgets();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenuWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenuWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> InventoryWidget;
	
	UUserWidget* CreateOrGetWidget(TObjectPtr<UUserWidget>& Widget, TSubclassOf<UUserWidget> WidgetClass);
	
	
};
