// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MainCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UPlayerInteractionComponent;

UCLASS()
class PARIAH_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Input
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* PlayerMappingContext;
	
	// Move Input
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveForward;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveBackwards;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveLeft;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveRight;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SprintAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CrouchAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;
	
	// Movement 
	UPROPERTY(EditAnywhere, Category = Movement)
	bool bIsSprinting = false;
	
	UPROPERTY(EditAnywhere, Category = Movement)
	bool bIsCrouching = false;
	
	UPROPERTY(EditAnywhere, Category = Movement)
	float WalkSpeed = 300.f;
	
	UPROPERTY(EditAnywhere, Category = Movement)
	float SprintSpeed = 600.f;
	
	
	void OnMoveForward(const FInputActionValue& Value);
	void OnMoveBackward(const FInputActionValue& Value);
	void OnMoveRight(const FInputActionValue& Value);
	void OnMoveLeft(const FInputActionValue& Value);
	void OnSprint(const FInputActionValue& Value);
	void OnCrouch(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);
	
	// Look Input
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;
	
	void OnLook(const FInputActionValue& Value);
	
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class UCameraComponent* Camera;
	
	// Interact Input
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* Interact;
	
	void OnInteract();

	// Interaction logic lives in this component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
	UPlayerInteractionComponent* InteractionComponent;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:
	
	float ForwardInput = 0.0f;
	float BackwardInput = 0.0f;
	float LeftInput = 0.0f;
	float RightInput = 0.0f;
};
