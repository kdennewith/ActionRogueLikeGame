// Fill out your copyright notice in the Description page of Project Settings.


#include "RLActionSystemComponent.h"


URLActionSystemComponent::URLActionSystemComponent()
{
}

/** Controls the Health Changes of the PlayerCharacter */
void URLActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = Attributes.Health; /* Never should be allowed to go Below 0 */
	
	float MaxHealth = GetDefault<URLActionSystemComponent>()->Attributes.Health;
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.f, MaxHealth); /* Changes the Health Value based on the InValueChange */
	
	if (!FMath::IsNearlyZero(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);	
	}
	
	UE_LOG(LogTemp, Log, TEXT("Health Changed %f, Max Health: %f"), Attributes.Health, MaxHealth);
}


