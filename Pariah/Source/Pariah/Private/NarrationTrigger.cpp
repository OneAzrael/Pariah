// Fill out your copyright notice in the Description page of Project Settings.


#include "NarrationTrigger.h"
#include "Components/BoxComponent.h"
#include "Player/MainCharacter.h"

ANarrationTrigger::ANarrationTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 100.f)); // size of the trigger
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));   // overlaps, doesn't block
}

void ANarrationTrigger::BeginPlay()
{
	Super::BeginPlay();

	// Listen for anything entering the box.
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ANarrationTrigger::OnOverlap);
}

void ANarrationTrigger::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Only react to the player.
	if (AMainCharacter* Player = Cast<AMainCharacter>(OtherActor))
	{
		if (bFireOnce && bHasFired) return; // already shown once
		bHasFired = true;

		Player->ShowNarration(NarrationLine);
	}
}



