// Fill out your copyright notice in the Description page of Project Settings.


#include "RLInteractionComponent.h"

#include "RLGameTypes.h"
#include "Core/RLInteractionInterface.h"
#include "Engine/OverlapResult.h"

TAutoConsoleVariable<bool> CVarIntercationDebugDrawing(TEXT("game.interaction.DebugDraw"), false,
	TEXT("Enable interaction component debug rendering. (0 = off, 1 = enabled"),
	ECVF_Cheat);

URLInteractionComponent::URLInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void URLInteractionComponent::Interact()
{
	if (SelectedActor)
	{
		IRLInteractionInterface::Execute_Interact(SelectedActor);
	}
	
}

void URLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	FVector Center = PC->GetPawn()->GetActorLocation();
	FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION; /** An ECC TraceChannel, Engine Settings */
	FCollisionShape Shape;
	TArray<FOverlapResult> Overlaps;
	
	Shape.SetSphere(InteractionRadius);
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	AActor* BestActor = nullptr;
	float HighestWeight = 0.f;
	float InteractionRadiusSqrd {InteractionRadius * InteractionRadius};
	
	bool bEnabledDebugDraw = CVarIntercationDebugDrawing.GetValueOnGameThread(); /* A Switch for Enabling the Debug Drawings in the Code Below */
	
	for (FOverlapResult& Overlap : Overlaps)
	{	
		FVector Origin;
		FVector BoxExtends;
		Overlap.GetActor()->GetActorBounds(true, Origin, BoxExtends); /* Never use ChildActorComponent */
		
		FVector OverlapDirection = (Origin - CameraLocation).GetSafeNormal();
		
		float DistanceToSqrd = (Origin - Center).SizeSquared(); /* Use SizeSquared to optimize */
		float NormalizedDistanceTo = 1.f - (DistanceToSqrd / InteractionRadiusSqrd); /* Normalized and inverted, smaller is higher weight */ 
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		float NormalizedDotResult = DotResult * 0.5f + 0.5f; /* If the value is negative, it's 0 <= x < 0.5, 0.5 is 0, if it's positive, then 0.5 < x <= 1.0 */
		
		float Weight = (NormalizedDotResult + NormalizedDistanceTo) + (NormalizedDistanceTo * DistanceToWeightScale);
		if (Weight > HighestWeight)
		{
			BestActor = Overlap.GetActor();
			HighestWeight = Weight;
		}
		
		if (bEnabledDebugDraw)
		{
			DrawDebugBox(GetWorld(), Origin, FVector(50.0f), FColor::Red);
			FString DebugString = FString::Printf(TEXT("Weight %f, DOT: %f, Dist %f"), Weight, NormalizedDotResult, NormalizedDistanceTo);
			DrawDebugString(GetWorld(), Origin, DebugString, nullptr, FColor::White, 0.f, true);
		}
	}
	
	SelectedActor = BestActor;
	if (bEnabledDebugDraw)
	{
		if (BestActor)
		{ 
			DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
		}
	
		DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	}
}

