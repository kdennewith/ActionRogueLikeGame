// Fill out your copyright notice in the Description page of Project Settings.


#include "RLActionSystemComponent.h"


URLActionSystemComponent::URLActionSystemComponent()
{
}

/** Controls the Health Changes of the PlayerCharacter */
void URLActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	Attributes.Health += InValueChange; /* Changes the Health Value based on the InValueChange */
	
}


