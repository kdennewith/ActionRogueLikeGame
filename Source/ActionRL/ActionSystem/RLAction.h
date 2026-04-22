// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RLAction.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRL_API URLAction : public UObject
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FName ActionName = FName("PrimaryAttack");
	
public:
	/** Getter for the Actors ActionName */
	FName GetActionName() const { return ActionName; }
	
	/** Starts an Actor Action */
	void StartAction();
	
};
