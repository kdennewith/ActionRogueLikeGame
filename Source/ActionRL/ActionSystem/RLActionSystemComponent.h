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
		: Health(100.0f), HealthMax(100.0f) {}
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
	
	UPROPERTY(BlueprintReadOnly)
	float HealthMax;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRL_API URLActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	/** Function to change the Health Values of an Actor */
	void ApplyDamage(float InValueChange);
	
	void ApplyHealing(float inHealthValue);
	
	bool IsFullHealth() const;
	
	float GetHealth() const;
	
	float GetMaxHealth() const;
	
	UPROPERTY(BlueprintAssignable) /* BlueprintAssignable is C++ Delegate specific */
	FOnHealthChanged OnHealthChanged;
	
protected:
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FRogueAttributeSet Attributes {}; /* The set of Attributes used by the PlayerCharacter */
	
public:
	
	URLActionSystemComponent();
};