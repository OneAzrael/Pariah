// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PARIAH_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	AMainMenuGameMode();
	
	protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenuWidget;
};
