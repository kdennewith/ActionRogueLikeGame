// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLActionSystemComponent.generated.h"

class URLAction;
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
	
protected:
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FRogueAttributeSet Attributes {}; /* The set of Attributes used by the PlayerCharacter */
	
	UPROPERTY()
	TArray<TObjectPtr<URLAction>> Actions; /* An array to hold all the Actions for the Character */
	
public:
	
	URLActionSystemComponent();
	
	/* Initializes the Component on Level Startup */
	virtual void InitializeComponent() override;
	
	/* BlueprintAssignable is C++ Delegate specific */
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	/** Function to Apply Damage to an Actor */
	void ApplyDamage(float InValueChange);
	
	/** Function to Apply Healing to an Actor */
	void ApplyHealing(float inHealthValue);
	
	/** Checks if the Health of the Actor is full */
	bool IsFullHealth() const;
	
	/** Gets the Health of the Actor */
	float GetHealth() const;
	
	/** Gets the Max Health of the Actor */
	float GetMaxHealth() const;
	
	/** Starts an Actor Action */
	void StartAction(FName InActionName);
};