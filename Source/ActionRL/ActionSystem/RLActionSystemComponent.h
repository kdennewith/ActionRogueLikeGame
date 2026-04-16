// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLActionSystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FRogueAttributeSet /* Holds the Attributes for the PlayerCharacter */
{
	GENERATED_BODY()
	
	FRogueAttributeSet()
		: Health(100.0f) {}
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRL_API URLActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	/** Function to change the Health Values of an Actor */
	void ApplyHealthChange(float InValueChange);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
protected:
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FRogueAttributeSet Attributes {}; /* The set of Attributes used by the PlayerCharacter */
	
public:
	
	URLActionSystemComponent();
};