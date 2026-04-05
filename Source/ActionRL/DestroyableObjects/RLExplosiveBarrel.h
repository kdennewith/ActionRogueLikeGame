// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLExplosiveBarrel.generated.h"

class UNiagaraComponent;
class URadialForceComponent;
class UNiagaraSystem;

UCLASS()
class ACTIONRL_API ARLExplosiveBarrel : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent; /** For the Barrel Mesh */
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent; /** For the Explosion Force */
	
	UPROPERTY(EditDefaultsOnly, Category="Explosive Barrel Traits")
	float ExplosionDelay = 3.0f; /** Put this in Explosive Barrel Traits in the Blueprint, set it's default to 3.0 seconds. */
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;  /** The Explosion Effect using a Niagara Animation */
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> FlamesEffect; /** The Flame Effect using a Niagara Animation */
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound; /** The Explosion Sound using USoundBase */
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> AftermathSound; /** The Aftermath of the Explosion Sound using USoundBase */
	
	void Explode(); /** The Explode Function */
	
	bool bExploded = false; /** boolean Exploded: if the Barrel has Exploded */
	
	FTimerHandle ExplosionTimerHandle; /** For keeping a timer for the Explosion countdown */
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningEffectComp = nullptr; /** For when the Barrel is burning after being Hit */
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveBurningSoundComp = nullptr; /** For the barrel sizzle type noise to Play tsss */

public:
	
	// Sets default values for this actor's properties
	ARLExplosiveBarrel();
	
	/** This is for keeping track of when the Barrel is damage so it can go Boom */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
