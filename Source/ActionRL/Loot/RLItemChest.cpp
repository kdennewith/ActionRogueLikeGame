// Fill out your copyright notice in the Description page of Project Settings.


#include "RLItemChest.h"

ARLItemChest::ARLItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	/** The Base and the Lid of the Chest */
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComponent = BaseMeshComponent;
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComponent->SetupAttachment(BaseMeshComponent); /** Attached to the BaseMesh */
	
	
}

void ARLItemChest::Interact()
{
	SetActorTickEnabled(true); /** Play Animation of the Chest opening on Interaction (From the RLInteractionInterface) */
}


void ARLItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void ARLItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentAnimationPitch = FMath::FInterpConstantTo(CurrentAnimationPitch, AnimationTargetPitch, DeltaTime, AnimationSpeed);
	LidMeshComponent->SetRelativeRotation(FRotator(CurrentAnimationPitch, 0.f, 0.f));
	
	if (FMath::IsNearlyEqual(CurrentAnimationPitch, AnimationTargetPitch))
	{
		SetActorTickEnabled(false);
	}
	
	
}

