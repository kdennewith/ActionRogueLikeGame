// Fill out your copyright notice in the Description page of Project Settings.


#include "RLInteractionComponent.h"

#include "Engine/OverlapResult.h"


URLInteractionComponent::URLInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void URLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();
	
	ECollisionChannel CollisionChannel = ECC_Visibility;
	
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	
	AActor* BestActor = nullptr;
	float HighestDotResult = -1.f;
	
	for (FOverlapResult& Overlap : Overlaps)
	{	
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
		
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		
		FString DebugString = FString::Printf(TEXT("DOT: %f"), DotResult);
		
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.f, true);
		
		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
	}
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
	}
}

