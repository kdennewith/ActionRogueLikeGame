// Fill out your copyright notice in the Description page of Project Settings.


#include "RLGameplayStatics.h"

#include "RLGameplayTags.h"
#include "ActionSystem/RLActionSystemComponent.h"

bool URLGameplayStatics::IsFullHealth(URLActionSystemComponent* ActionComp)
{
	FRLAttribute* Health = ActionComp->GetAttribute(RLGameplayTags::Attribute_Health);
	FRLAttribute* HealthMax = ActionComp->GetAttribute(RLGameplayTags::Attribute_HealthMax);

	return FMath::IsNearlyEqual(Health->GetValue(), HealthMax->GetValue());
}
