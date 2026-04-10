// Fill out your copyright notice in the Description page of Project Settings.


#include "RLProjectileTeleport.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARLProjectileTeleport::ARLProjectileTeleport()
{
	ProjectileMovementComponent->InitialSpeed = 7000.f;
}

void ARLProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::StartDelayedTeleport, DetonateDelay);
}

void ARLProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/* Skipping to handle a delayed destruction of the Projectile to avoid 2 Explosion Effects */
	//Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	/* Cancelling the timer so that a second Teleportation doesn't happen */
	GetWorldTimerManager().ClearTimer(TeleportHandle);
	
	StartDelayedTeleport();
}

void ARLProjectileTeleport::StartDelayedTeleport()
{
	PlayExplodeEffects();
	
	ProjectileMovementComponent->StopMovementImmediately();
	
	LoopedNiagaraComponent->Deactivate();
	LoopedAudioComponent->Stop();
	SetActorEnableCollision(false);
	
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::HandleTeleportation, TeleportSecondaryDelay);
	
}

void ARLProjectileTeleport::HandleTeleportation()
{
	APawn* ActorToTeleport = GetInstigator();
	// todo: Check if Instigator is still valid/alive once Death is Implemented.
	check(ActorToTeleport)
	
	/* So that the Actor doesn't get Stuck in a Wall or some Geometry by chance 
	 * This also may fail if the location is not valid for Teleportation.
	 */
	ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	
	Destroy(); /* Destroying the Projectile, can't do sooner because of timers not being able to act on an Actor */
}





