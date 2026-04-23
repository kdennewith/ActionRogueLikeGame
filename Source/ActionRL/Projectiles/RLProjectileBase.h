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
class USoundBase;

UCLASS(Abstract)
class ACTIONRL_API ARLProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	
	/** The Sphere Component for the Projectile */
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	/** The Movement Component for the Projectile; controls speed, movement. */
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	/** For an Audio Component for the Projectile to have Sound. */
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	/** For SFX Niagara Component of the Projectile */
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	/** For SFX Niagara Component for the Hit Effect */
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	/** For Sound Effect for the Hit Effect. */
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	/*- Protected Functions ------------------------------------------------------------------------------------------*/
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
	void PlayExplodeEffects();
	
public:
	
	ARLProjectileBase();
	
	virtual void PostInitializeComponents() override;

};
