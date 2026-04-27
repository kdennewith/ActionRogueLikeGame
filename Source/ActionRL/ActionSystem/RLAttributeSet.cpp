// Fill out your copyright notice in the Description page of Project Settings.


#include "RLAttributeSet.h"

#include "RLActionSystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


//- Constructors  ------------------------------------------------------------

URLHealthAttributeSet::URLHealthAttributeSet() : Health(100.f), HealthMax(100.f) {}

URLPawnAttributeSet::URLPawnAttributeSet() : MoveSpeed(FRLAttribute(550)) {}

URLPlayerAttributeSet::URLPlayerAttributeSet()
{
	
}

URLMonsterAttributeSet::URLMonsterAttributeSet()
{
	MoveSpeed = FRLAttribute(450);
}

/** Called during Initialization of the ActionSystemComponent */
void URLPawnAttributeSet::InitializeAttributes()
{
	Super::InitializeAttributes();
	
	ApplyMoveSpeed();
}

//- PostAttributeChanged Functions --------------------------------------

void URLHealthAttributeSet::PostAttributeChanged()
{
	Health.Base = FMath::Clamp(Health.Base, 0.f, HealthMax.GetValue());
}

void URLPawnAttributeSet::PostAttributeChanged()
{
	Super::PostAttributeChanged();
	
	ApplyMoveSpeed();
	
}



void URLPawnAttributeSet::ApplyMoveSpeed()
{
	/** Setting the Characters Movespeed with the PawnAttributeSet's MoveSpeed Value */
	ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningComponent()->GetOwner());
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed.GetValue();
}

//- Get Functions ----------------------------------------------------------------

URLActionSystemComponent* URLAttributeSet::GetOwningComponent() const
{
	return Cast<URLActionSystemComponent>(GetOuter());
}
