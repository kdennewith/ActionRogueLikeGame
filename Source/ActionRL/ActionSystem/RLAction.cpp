// Fill out your copyright notice in the Description page of Project Settings.


#include "RLAction.h"

void URLAction::StartAction()
{
	
	float GameTime = 0.f;
	
	//GetWorld()->TimeSeconds;
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName}", 
		("ActionName", ActionName));
}
