// Fill out your copyright notice in the Description page of Project Settings.


#include "RLActionSystemComponent.h"
#include "RLAction.h"
#include "RLAttributeSet.h"

/** Constructor */
URLActionSystemComponent::URLActionSystemComponent()
{
	bWantsInitializeComponent = true;
	
	AttributeSetClass = URLAttributeSet::StaticClass();
}

/* Initializes the Component on Level Startup, Fills up the Action Array */
void URLActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	Attributes = NewObject<URLAttributeSet>(this, AttributeSetClass);
	
	for (TFieldIterator<FStructProperty> PropIt(Attributes->GetClass()); PropIt; ++PropIt)
	{
		/* Right now it's just HP and HP MAX is all the Attributes */
		FRLAttribute* FoundAttribute = PropIt->ContainerPtrToValuePtr<FRLAttribute>(Attributes);
		
		 /* Getting the name of the Tag as an FName */
		FName AttributeTagName = FName("Attribute." + PropIt->GetName());
		
		/* Using the FName to get the GameplayTag */
		FGameplayTag AttributeTag = FGameplayTag::RequestGameplayTag(AttributeTagName);
		
		CachedAttributes.Add(AttributeTag ,FoundAttribute);
	}
	
	for (TSubclassOf<URLAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
}

/** Starts an Actors Action if the Action Exists */
void URLActionSystemComponent::StartAction(FGameplayTag InActionName)
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
void URLActionSystemComponent::StopAction(FGameplayTag InActionName)
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

void URLActionSystemComponent::ApplyAttributeChange(FGameplayTag AttributeTag, float InValue, EAttributeModifyType ModifyType)
{
	FRLAttribute* FoundAttribute = GetAttribute(AttributeTag);
	check(FoundAttribute);
	
	FoundAttribute->Modifier += InValue;
	
	switch (ModifyType)
	{
	case EAttributeModifyType::Base:
		FoundAttribute->Base += InValue;
		break;
	case EAttributeModifyType::Modifier:
		FoundAttribute->Modifier += InValue;
		break;
	case EAttributeModifyType::OverrideBase:
		FoundAttribute->Base = InValue;
		break;
	case EAttributeModifyType::Invalid:
		FoundAttribute->Base += InValue;
		break;
	default:
		check(false);
	}
	
	/* Clamps the Attribute Change */
	Attributes->PostAttributeChanged();
	
	UE_LOGFMT(LogTemp, Log, "Attribute: {0}, New: {1}");
}

FRLAttribute* URLActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag)
{
	/* A Pointer to a Pointer */
	FRLAttribute** FoundAttribute = CachedAttributes.Find(InAttributeTag);
	return *FoundAttribute;
}


