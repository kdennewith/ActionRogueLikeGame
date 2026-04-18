// Fill out your copyright notice in the Description page of Project Settings.


#include "RLActionSystemComponent.h"


URLActionSystemComponent::URLActionSystemComponent()
{
}

/** Controls the Health Changes of the PlayerCharacter */
void URLActionSystemComponent::ApplyDamage(float InValueChange)
{
	float OldHealth = Attributes.Health; /* Never should be allowed to go Below 0 */
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.f, Attributes.HealthMax); /* Changes the Health Value based on the InValueChange, ensure that it's between 0.f and Attributes.HealthMax */
	
	if (!FMath::IsNearlyZero(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}
	
	UE_LOG(LogTemp, Log, TEXT("Health Changed %f, Max Health: %f"), Attributes.Health, Attributes.HealthMax);
}

void URLActionSystemComponent::ApplyHealing(float inHealthValue)
{
	float OldHealth = Attributes.Health; /* Never should be allowed to go Below 0 */
	
	Attributes.Health = FMath::Clamp(Attributes.Health + inHealthValue, 0.f, Attributes.HealthMax); /* Changes the Health Value based on the InValueChange, ensure that it's between 0.f and Attributes.HealthMax */
	
	OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	
	
	UE_LOG(LogTemp, Log, TEXT("Health Changed %f, Max Health: %f"), Attributes.Health, Attributes.HealthMax);
}


/** Checks if the Player is Full Health or Not */
bool URLActionSystemComponent::IsFullHealth()
{
	bool bIsFullHealth = false;
	if (FMath::IsNearlyEqual(Attributes.HealthMax, Attributes.Health))
	{
		bIsFullHealth = true;
	}
	return bIsFullHealth;
}


