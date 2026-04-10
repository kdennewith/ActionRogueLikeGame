// Fill out your copyright notice in the Description page of Project Settings.


#include "RLProjectileBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARLProjectileBase::ARLProjectileBase()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComponent;
	SphereComponent->SetSphereRadius(16.f);
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f; /* So the Projectile doesn't fall through the floor */
	
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);
	
	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComp"));
	LoopedAudioComponent->SetupAttachment(SphereComponent);
}

void ARLProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &ARLProjectileBase::OnActorHit);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true); /* Gets the person who instigated the attack so they don't get hit, in other words the Player */
}

/** What happens when the Projectile hits and Actor */
void ARLProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	PlayExplodeEffects();
	
	Destroy(); /* Destroys the Object */
}

/** Plays the Explosion Effects for 'this' Actor UObject */
void ARLProjectileBase::PlayExplodeEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation()); /* Plays the Explosion Effect at the Actor Location it hit */
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation()); /* Plays the Explosion Sounds at the Actor Location */
}


