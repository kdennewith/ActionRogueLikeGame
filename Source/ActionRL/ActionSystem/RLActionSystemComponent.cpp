// Fill out your copyright notice in the Description page of Project Settings.


#include "RLActionSystemComponent.h"
#include "RLAction.h"

/** Constructor */
URLActionSystemComponent::URLActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

/* Initializes the Component on Level Startup, Fills up the Action Array */
void URLActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	for (TSubclassOf<URLAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
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

/** Function to Apply Healing to an Actor */
void URLActionSystemComponent::ApplyHealing(float inHealthValue)
{
	float OldHealth = Attributes.Health; /* Never should be allowed to go Below 0 */
	
	Attributes.Health = FMath::Clamp(Attributes.Health + inHealthValue, 0.f, Attributes.HealthMax); /* Changes the Health Value based on the InValueChange, ensure that it's between 0.f and Attributes.HealthMax */
	
	OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	
	
	UE_LOG(LogTemp, Log, TEXT("Health Changed %f, Max Health: %f"), Attributes.Health, Attributes.HealthMax);
}


/** Checks if the Player is Full Health or Not */
bool URLActionSystemComponent::IsFullHealth() const
{
	bool bIsFullHealth = false;
	if (FMath::IsNearlyEqual(Attributes.HealthMax, Attributes.Health))
	{
		bIsFullHealth = true;
	}
	return bIsFullHealth;
}

/** Gets the Health of the ActionSystemComp */
float URLActionSystemComponent::GetHealth() const
{
	return Attributes.Health;
}

/** Gets the Max Health of the ActionComp */
float URLActionSystemComponent::GetMaxHealth() const
{
	return Attributes.HealthMax;
}

/** Starts an Actors Action if the Action Exists */
void URLActionSystemComponent::StartAction(FName InActionName)
{
	//todo: Add a linear time search with a Map instead of an Array.
	for (URLAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			if (Action->CanStart())
			{
				Action->StartAction();
			}
			return;
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("Action %s not found"), *InActionName.ToString()) // For Logging if Needed
}

/* Stops an Action like on Sprinting */
void URLActionSystemComponent::StopAction(FName InActionName)
{
	for (URLAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("Action %s not found"), *InActionName.ToString()) // For Logging if Needed
}

/** Grants Actions/Abilities to the RLActionSystemComponent as an Array in Actions */
void URLActionSystemComponent::GrantAction(TSubclassOf<URLAction> NewActionClass)
{
	URLAction* NewAction = NewObject<URLAction>(this, NewActionClass);
	Actions.Add(NewAction);
}


