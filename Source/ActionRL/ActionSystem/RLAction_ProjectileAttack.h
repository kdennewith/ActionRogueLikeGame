// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLAction.h"
#include "RLAction_ProjectileAttack.generated.h"

class URLActionSystemComponent;
class ARLProjectileBase;
class UNiagaraSystem;
class USoundBase;
class UAnimMontage;
/**
 * 
 */
UCLASS(Abstract)
class ACTIONRL_API URLAction_ProjectileAttack : public URLAction
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="ProjectileAttack")
	TSubclassOf<ARLProjectileBase> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="ProjectileAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="ProjectileAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(VisibleAnywhere, Category="ProjectileAttack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category="ProjectileAttack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
public:
	
	URLAction_ProjectileAttack();
	
	virtual void StartAction_Implementation() override;
	
	void AttackTimerElapsed();
	
};
