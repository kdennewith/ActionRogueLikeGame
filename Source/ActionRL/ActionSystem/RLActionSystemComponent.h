// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLActionSystemComponent.generated.h"


struct FRogueAttributeSet
{
	FRogueAttributeSet()
		: Health(100.0f) {}
	
	float Health;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRL_API URLActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	void ApplyHealthChange(float InValueChange);
	
protected:
	
	FRogueAttributeSet Attributes {};
	
public:
	
	URLActionSystemComponent();
};