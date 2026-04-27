// Fill out your copyright notice in the Description page of Project Settings.


#include "RLAttributeSet.h"



URLHealthAttributeSet::URLHealthAttributeSet() : 
Health(100.f), /** The Base Health */
HealthMax(100.f)
{}

void URLHealthAttributeSet::PostAttributeChanged()
{
	Health.Base = FMath::Clamp(Health.Base, 0.f, HealthMax.GetValue());
}