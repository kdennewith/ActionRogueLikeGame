// Fill out your copyright notice in the Description page of Project Settings.


#include "RLProjectileBlackhole.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ARLProjectileBlackhole::ARLProjectileBlackhole()
{
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(SphereComponent);
	
	RadialForceComponent->ForceStrength = -1000000.f; /* For Force instead of Impulse like in the ExplosiveBarrel.cpp */
	RadialForceComponent->Radius = 750.f; /* How big the Succ component is */
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn)); /* Avoids the Player being sucked in, removes the suckage of Pawns */
	
	SphereComponent->SetSphereRadius(20.f); /* The size of the Sphere, so it makes things swirl around it. */
	SphereComponent->SetCollisionProfileName("BlackholeCore"); /* For the Collision Profile in Editor */
	ProjectileMovementComponent->InitialSpeed = 500.f; /* The speed the Projectile comes out initially */
	
	InitialLifeSpan = 5.f; /* How long the Projectile will be "Alive" This calls Destroy(), SUPER HANDY */
	
}

void ARLProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARLProjectileBlackhole::OnSphereOverlappedActor);
}

void ARLProjectileBlackhole::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFronSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}


