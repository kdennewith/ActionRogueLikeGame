// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLProjectileBase.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UAudioComponent;

UCLASS(Abstract)
class ACTIONRL_API ARLProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	/** The base traits for a Projectile object */
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
	void PlayExplodeEffects();
	
public:
	
	virtual void PostInitializeComponents() override;
	
	ARLProjectileBase();

};
