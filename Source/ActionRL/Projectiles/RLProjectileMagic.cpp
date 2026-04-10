// Fill out your copyright notice in the Description page of Project Settings.


#include "RLProjectileMagic.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"



/* Constructor, Sets Default Values */
ARLProjectileMagic::ARLProjectileMagic()
{
	ProjectileMovementComponent->InitialSpeed = 2000.f;
}

void ARLProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit); /* This is the Base Implementation located in RLProjectileBase.cpp */
	
	FVector HitFromDirection = GetActorRotation().Vector();
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, HitFromDirection, Hit, GetInstigatorController(),
		this, DmgTypeClass);
}




