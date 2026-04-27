// Fill out your copyright notice in the Description page of Project Settings.


#include "RLActionSystemComponent.h"
#include "Logging/StructuredLog.h"
#include "RLAction.h"
#include "RLAttributeSet.h"

/** Constructor */
URLActionSystemComponent::URLActionSystemComponent()
{
	bWantsInitializeComponent = true;
	
	/** Setting the Attribute Class to HealthAttribute Sets. Check the RLAttributeSet.cpp/h. */
	AttributeSetClass = URLHealthAttributeSet::StaticClass();
}


/* Initializes the Component on Level Startup, Fills up the Action Array */
void URLActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	Attributes = NewObject<URLAttributeSet>(this, AttributeSetClass);
	
	/** Making a Property Iterator to get Attributes from AttributeStructs */
	for (TFieldIterator<FStructProperty> PropIt(Attributes->GetClass()); PropIt; ++PropIt)
	{
		if (PropIt->Struct == FRLAttribute::StaticStruct())
		{
			FRLAttribute* FoundAttribute = PropIt->ContainerPtrToValuePtr<FRLAttribute>(Attributes);
			if (FoundAttribute)
			{
				/* Getting the name of the Tag as an FName. Attaching Attribute., which is the leading part of the Attribute name, to the Name. */
				FName AttributeTagName = FName("Attribute." + PropIt->GetName());
				
				/* Using the FName to get the GameplayTag */
				FGameplayTag AttributeTag = FGameplayTag::RequestGameplayTag(AttributeTagName);
				
				CachedAttributes.Add(AttributeTag ,FoundAttribute);
			}
		}
	}
	
	for (TSubclassOf<URLAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
	
}

void URLActionSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	/** Applies the MovementSpeed */
	Attributes->InitializeAttributes();
}

/** Grants Actions/Abilities to the RLActionSystemComponent as an Array in Actions */
void URLActionSystemComponent::GrantAction(TSubclassOf<URLAction> NewActionClass)
{
	URLAction* NewAction = NewObject<URLAction>(this, NewActionClass);
	Actions.Add(NewAction);
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
	
	UE_LOG(LogTemp, Log, TEXT("Action %s not found"), *InActionName.ToString()); // For Logging if Needed
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
	
	UE_LOG(LogTemp, Log, TEXT("Action %s not found"), *InActionName.ToString()); // For Logging if Needed
}


void URLActionSystemComponent::ApplyAttributeChange(FGameplayTag InAttributeTag, float InValue, EAttributeModifyType ModifyType)
{
	FRLAttribute* FoundAttribute = GetAttribute(InAttributeTag);
	if (FoundAttribute == nullptr)
	{
		return;
	}
	
	/** The Old Value of the Attribute */
	float OldValue = FoundAttribute->GetValue();
	
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
	default:
		check(false);
	}
	
	/* Clamps the Attribute Change */
	Attributes->PostAttributeChanged();
	
	/* The event from the Attribute Listeners, a Map for linear time search */
	if (FOnAttributeChanged* Event = AttributeListeners.Find(InAttributeTag))
	{
		/* Broadcasts the Change on the Attribute */
		Event->Broadcast(InAttributeTag, FoundAttribute->GetValue(), OldValue);
	}
	
	UE_LOGFMT(LogTemp, Log, "Attribute: {AttributeTag}, New: {NewValue}", ("AttributeTag", InAttributeTag.ToString()), ("NewValue", FoundAttribute->GetValue()));
}

FRLAttribute* URLActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag)
{
	if (FRLAttribute* FoundAttribute = *CachedAttributes.Find(InAttributeTag))
	{
		return FoundAttribute;
	}
	return nullptr;
}

FOnAttributeChanged& URLActionSystemComponent::GetAttributeListener(FGameplayTag InAttributeTag)
{
	return AttributeListeners.FindOrAdd(InAttributeTag);
}


