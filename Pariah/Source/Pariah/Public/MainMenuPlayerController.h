// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PARIAH_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainMenuPlayerController();
	
	protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	
	// How far the camera goes left and right
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	float SwayRange = 15.0f;

	// How fast the camera sways
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	float SwaySpeed = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<AActor> MenuCameraClass;
	
private:
	float ElapsedTime = 0.0f;
	FRotator OriginalCameraRotation;
	TObjectPtr<AActor> CachedMenuCamera;
};
