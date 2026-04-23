// Fill out your copyright notice in the Description page of Project Settings.


#include "RLAction.h"

#include "RLActionSystemComponent.h"

void URLAction::StartAction_Implementation()
{
	bIsRunning = true;
	
	float GameTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", 
		("ActionName", ActionName),
		("WorldTime", GameTime));
}

void URLAction::StopAction_Implementation()
{
	bIsRunning = false;
	
	float GameTime = GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", 
		("ActionName", ActionName),
		("WorldTime", GameTime));
	
	CooldownUntil = GetWorld()->TimeSeconds + CooldownTime;
}

URLActionSystemComponent* URLAction::GetOwningComponent() const
{
	return Cast<URLActionSystemComponent>(GetOuter());
}

bool URLAction::CanStart()
{
	if (IsRunning())
	{
		return false;
	}
	
	if (GetCooldownTimeRemaining() > 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("CD Remaining %f"), GetCooldownTimeRemaining())
		return false;
	}
	
	return true;
}

float URLAction::GetCooldownTimeRemaining() const
{
	return FMath::Max(CooldownUntil - GetWorld()->TimeSeconds);
}


