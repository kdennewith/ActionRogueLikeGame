// Fill out your copyright notice in the Description page of Project Settings.


#include "RLInteractionComponent.h"



URLInteractionComponent::URLInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void URLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();
	
	DrawDebugBox(GetWorld(), Center, FVector(20.0f), FColor::Red);
}

