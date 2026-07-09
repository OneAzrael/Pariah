// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerInteractionComponent.h"
#include "InventoryComponent.h"
#include "NarrationWidget.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = true;

	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("InteractionComponent"));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	
	if (NarrationWidgetClass)
	{
		NarrationWidget = CreateWidget<UNarrationWidget>(GetWorld(), NarrationWidgetClass);
		if (NarrationWidget)
		{
			NarrationWidget->AddToViewport();
			NarrationWidget->ShowLine(FText::FromString(TEXT("Where am I... what happened?")));
		}
	}
}

void AMainCharacter::ShowNarration(const FText& Line)
{
	if (NarrationWidget)
	{
		NarrationWidget->ShowLine(Line);
	}
}

// Movement Input

void AMainCharacter::OnMoveForward(const FInputActionValue& Value)
{
	ForwardInput = Value.Get<float>();
}
void AMainCharacter::OnMoveBackward(const FInputActionValue& Value)
{
	BackwardInput = Value.Get<float>();
}

void AMainCharacter::OnMoveRight(const FInputActionValue& Value)
{
	RightInput = Value.Get<float>();
}

void AMainCharacter::OnMoveLeft(const FInputActionValue& Value)
{
	LeftInput = Value.Get<float>();
}

void AMainCharacter::OnSprint(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Sprinting"));
	
	bIsSprinting = Value.Get<bool>();
	GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
}

void AMainCharacter::OnCrouch(const FInputActionValue& Value)
{
	if (bIsCrouching)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
	bIsCrouching = !bIsCrouching;
}

void AMainCharacter::OnJump(const FInputActionValue& Value)
{

	Jump();
}

// Look Input

void AMainCharacter::OnLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void AMainCharacter::OnInteract()
{
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	float CombinedForward = ForwardInput - BackwardInput;
	float CombinedRight = RightInput - LeftInput;
	
	if (Controller)
	{
		if (CombinedForward != 0.0f)
			AddMovementInput(GetActorForwardVector(), CombinedForward);
    
		if (CombinedRight != 0.0f)
			AddMovementInput(GetActorRightVector(), CombinedRight);
	}
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent -> BindAction(MoveForward, ETriggerEvent::Triggered, this, &AMainCharacter::OnMoveForward);
		EnhancedInputComponent -> BindAction(MoveForward, ETriggerEvent::Completed, this, &AMainCharacter::OnMoveForward);
		
		EnhancedInputComponent -> BindAction(MoveBackwards, ETriggerEvent::Triggered, this, &AMainCharacter::OnMoveBackward);
		EnhancedInputComponent -> BindAction(MoveBackwards, ETriggerEvent::Completed, this, &AMainCharacter::OnMoveBackward);
		
		EnhancedInputComponent -> BindAction(MoveLeft, ETriggerEvent::Triggered, this, &AMainCharacter::OnMoveLeft);
		EnhancedInputComponent -> BindAction(MoveLeft, ETriggerEvent::Completed, this, &AMainCharacter::OnMoveLeft);
		
		EnhancedInputComponent -> BindAction(MoveRight, ETriggerEvent::Triggered, this, &AMainCharacter::OnMoveRight);
		EnhancedInputComponent -> BindAction(MoveRight, ETriggerEvent::Completed, this, &AMainCharacter::OnMoveRight);
		
		EnhancedInputComponent -> BindAction(CrouchAction, ETriggerEvent::Started, this, &AMainCharacter::OnCrouch);
		
		EnhancedInputComponent -> BindAction(SprintAction, ETriggerEvent::Started, this, &AMainCharacter::OnSprint);
		EnhancedInputComponent -> BindAction(SprintAction, ETriggerEvent::Completed, this, &AMainCharacter::OnSprint);
		
		EnhancedInputComponent -> BindAction(JumpAction, ETriggerEvent::Started, this, &AMainCharacter::OnJump);
		
		EnhancedInputComponent -> BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnLook);
		
		EnhancedInputComponent -> BindAction(Interact, ETriggerEvent::Started, InteractionComponent, &UPlayerInteractionComponent::TryInteract);
	}
}