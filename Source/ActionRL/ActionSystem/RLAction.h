// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RLAction.generated.h"

class URLActionSystemComponent;
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ACTIONRL_API URLAction : public UObject
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Actions")
	FName ActionName = FName("PrimaryAttack");
	
	UPROPERTY(EditDefaultsOnly, Category="Actions")
	float CooldownTime = 0.f;
	
	/* Gametime until the Action is Available again */
	UPROPERTY(Transient)
	float CooldownUntil = 0.f;
	
	UPROPERTY(Transient)
	bool bIsRunning = false;
	
public:
	
	/* Gets the Parent Component */
	UFUNCTION(BlueprintCallable)
	URLActionSystemComponent* GetOwningComponent() const;
	
	/** Starts an Actor Action */
	UFUNCTION(BlueprintNativeEvent, Category="Actions")
	void StartAction();
	
	/** Starts an Actor Action */
	UFUNCTION(BlueprintNativeEvent, Category="Actions")
	void StopAction();
	
	/** Getter for the Actors ActionName */
	FName GetActionName() const { return ActionName; }
	
	bool CanStart();
	
	bool IsRunning() const { return bIsRunning; }
	
	float GetCooldownTimeRemaining() const;
};
