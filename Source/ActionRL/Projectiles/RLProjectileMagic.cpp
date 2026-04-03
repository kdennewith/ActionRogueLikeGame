// Fill out your copyright notice in the Description page of Project Settings.


#include "RLProjectileMagic.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

// Sets default values
ARLProjectileMagic::ARLProjectileMagic()
{
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComponent;
	SphereComponent->SetSphereRadius(16.f);
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagara"));
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f; /* So the Projectile doesn't fall through the floor */
	
}


