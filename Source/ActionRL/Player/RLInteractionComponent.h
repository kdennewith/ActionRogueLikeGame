// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRL_API URLInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float InteractionRadius {800.f};
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float DistanceToWeightScale {2.f};
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float DirectionWeightScale {1.f};
	
	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;

public:
	/** The Constructor */
	URLInteractionComponent();
	
	void Interact();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
