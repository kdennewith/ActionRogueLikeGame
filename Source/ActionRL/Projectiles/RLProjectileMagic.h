// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLProjectileBase.h"
#include "RLProjectileMagic.generated.h"

class UDamageType;
class UNiagaraSystem;

UCLASS(Abstract)
class ACTIONRL_API ARLProjectileMagic : public ARLProjectileBase
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DmgTypeClass;
	
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override; /* Overriding the base implementation */
	
public:
	
	ARLProjectileMagic();
};
