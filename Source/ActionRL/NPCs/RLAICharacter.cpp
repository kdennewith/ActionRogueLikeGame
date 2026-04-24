// Fill out your copyright notice in the Description page of Project Settings.


#include "RLAICharacter.h"

#include "RLGameplayTags.h"
#include "ActionSystem/RLActionSystemComponent.h"


ARLAICharacter::ARLAICharacter()
{
	ActionSystemComponent = CreateDefaultSubobject<URLActionSystemComponent>(TEXT("ActionSystemComp"));
}

float ARLAICharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	ActionSystemComponent->ApplyAttributeChange(RLGameplayTags::Attribute_Health, -DamageAmount, EAttributeModifyType::Base);
	
	return ActualDamage;
}




