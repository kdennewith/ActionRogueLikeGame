// Fill out your copyright notice in the Description page of Project Settings.


#include "RLPickupBase.h"

#include "Components/SphereComponent.h"


// Sets default values
ARLPickupBase::ARLPickupBase()
{
	PickupRangeComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PickupRangeComponent")); /* The PickUp Orb around the player */
	PickupRangeComponent->SetSphereRadius(150.f); /* Setting the Sphere size */
	PickupRangeComponent->SetCollisionProfileName(TEXT("Pickups")); /* Setting the Collision Profile name of the Pickup Sphere Component */
	RootComponent = PickupRangeComponent; /* Setting the Sphere as the root component of the Pickup item */
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMeshComp")); /* The Mesh Component for the Pickup */
	BaseMeshComponent->SetCollisionProfileName("NoCollision"); /* So you can Ghost through items without them colliding with A Player */
	BaseMeshComponent->SetupAttachment(RootComponent); /* Attaching it to the Sphere */
	
	PickupSoundComponent = CreateDefaultSubobject<USoundBase>(TEXT("Pickup Sound"));
}

void ARLPickupBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	PickupRangeComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorOverlapped);
}

void ARLPickupBase::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFronSweep, const FHitResult& SweepResult)
{
	/* Do Nothin, something in the Derived classes only */
}


