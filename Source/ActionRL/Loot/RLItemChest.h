// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RLInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "RLItemChest.generated.h"

UCLASS()
class ACTIONRL_API ARLItemChest : public AActor, public IRLInteractionInterface
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent; /* For the Chest itself, the base of it without the lid */
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent; /** For the lid of the Chest */
	
	UPROPERTY(VisibleAnywhere, Category="Animation")
	float AnimationSpeed = 50.f;
	
	UPROPERTY(VisibleAnywhere, Category="Animation")
	float AnimationTargetPitch = 120.f;
	
	float CurrentAnimationPitch = 0.f;
	
	virtual void BeginPlay() override;

public:
	
	ARLItemChest();
	
	virtual void Interact() override;
	
	virtual void Tick(float DeltaTime) override;
};
