// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"
#include "camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CachedMenuCamera = UGameplayStatics::GetActorOfClass(GetWorld(), MenuCameraClass);
	if (CachedMenuCamera)
	{
		OriginalCameraRotation = CachedMenuCamera->GetActorRotation();
		SetViewTargetWithBlend(CachedMenuCamera, 0.0f);
	}
}

void AMainMenuPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	float Yaw = FMath::Sin(ElapsedTime * SwaySpeed) * SwayRange;

	if (CachedMenuCamera)
	{
		FRotator NewRot = OriginalCameraRotation;
		NewRot.Yaw = OriginalCameraRotation.Yaw + Yaw;
		CachedMenuCamera->SetActorRotation(NewRot);
	}
}