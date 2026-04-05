// Fill out your copyright notice in the Description page of Project Settings.


#include "RLExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ARLExplosiveBarrel::ARLExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComponent->SetSimulatePhysics(true); /** The Barrel will have Physics because of this */
	
	MeshComponent->SetCollisionProfileName("PhysicsActor"); /** Need to set this in C++ */
	RootComponent = MeshComponent; /** The Root Component of RLExplosiveBarrel is set to the Mesh (A Barrel) */
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComponent->SetupAttachment(MeshComponent); /** Attaching it to the Barrel Mesh */
	
	RadialForceComponent->ImpulseStrength = 150000.f;
	RadialForceComponent->Radius = 750.f;
	
	RadialForceComponent->bAutoActivate = false; /** So it's not perma Rotato Force */
	RadialForceComponent->bIgnoreOwningActor = true;
	
	
	
}

float ARLExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (bExploded || GetWorldTimerManager().TimerExists(ExplosionTimerHandle))
	{
		return ActualDamage;
	}
	
	ActiveBurningEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(FlamesEffect, MeshComponent, NAME_None,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	ActiveBurningSoundComp = UGameplayStatics::SpawnSoundAttached(AftermathSound, MeshComponent);
	
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ARLExplosiveBarrel::Explode, ExplosionDelay);
	
	return ActualDamage;
}

void ARLExplosiveBarrel::Explode()
{
	bExploded = true; /** Sets the Barrel trait Exploded to True */
	
	ActiveBurningEffectComp->Deactivate(); /** Deactivating the Burning Effect when the Barrel Explodes */
	ActiveBurningSoundComp->Stop(); /** Stops the burning Sound when the Barrel Explodes */
	
	RadialForceComponent->FireImpulse(); /** This triggers the Impulse set in the Constructor */
	
	/** For the Explosion Effect to spawn AT THE LOCATION of 'this' */
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator);
	
	/** For the Explosion Sound to spawn AT THE LOCATION of 'this */
	UGameplayStatics::SpawnSoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
}

// Called every frame
void ARLExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

