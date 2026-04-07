// Fill out your copyright notice in the Description page of Project Settings.


#include "RLInteractionComponent.h"

#include "RLGameTypes.h"
#include "Core/RLInteractionInterface.h"
#include "Engine/OverlapResult.h"


URLInteractionComponent::URLInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void URLInteractionComponent::Interact()
{
	IRLInteractionInterface* InteractInterface = Cast<IRLInteractionInterface>(SelectedActor);
	if (InteractInterface)
	{
		InteractInterface->Interact();
	}
}

void URLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	FVector Center = PC->GetPawn()->GetActorLocation();
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION; /** An ECC TraceChannel, Engine Settings */
	FCollisionShape Shape;
	TArray<FOverlapResult> Overlaps;
	
	Shape.SetSphere(InteractionRadius);
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	AActor* BestActor = nullptr;
	float HighestDotResult = -1.f;
	for (FOverlapResult& Overlap : Overlaps)
	{	
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
		
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
		FString DebugString = FString::Printf(TEXT("DOT: %f"), DotResult);
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.f, true);
	}
	
	SelectedActor = BestActor;
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
	}
	
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
}

