// Fill out your copyright notice in the Description page of Project Settings.


#include "RLBTDecorator_IsLowHealth.h"

#include "AIController.h"
#include "RLGameplayTags.h"
#include "ActionSystem/RLActionSystemComponent.h"

bool URLBTDecorator_IsLowHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	check(Pawn);
	
	URLActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URLActionSystemComponent>();
	/* Checking if the current health % is lower than the LowHealthThreshold of 30% */
	if ((ActionComp->GetAttribute(RLGameplayTags::Attribute_Health)->GetValue() / 
		ActionComp->GetAttribute(RLGameplayTags::Attribute_HealthMax)->GetValue())<= LowHealthThreshold)
	{
		return true;
	}
	
	
	/* If the function returns here, that means there was no ActionComp, which is not good */
	return false;
}
