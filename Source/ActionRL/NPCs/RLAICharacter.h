// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RLAICharacter.generated.h"

class URLActionSystemComponent;

UCLASS()
class ACTIONRL_API ARLAICharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<URLActionSystemComponent> ActionSystemComponent; /* Controls the Attributes of the ARLAICharacter, Health for example. */
	
public:
	
	ARLAICharacter();
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
};
