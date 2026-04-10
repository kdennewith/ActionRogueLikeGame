// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLProjectileBase.h"
#include "GameFramework/Actor.h"
#include "RLProjectileTeleport.generated.h"

UCLASS()
class ACTIONRL_API ARLProjectileTeleport : public ARLProjectileBase
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Timers")
	FTimerHandle TeleportHandle;
	
	UPROPERTY(EditDefaultsOnly, Category="Timers")
	float TeleportSecondaryDelay = 0.2;
	
	UPROPERTY(EditDefaultsOnly, Category="Timers")
	float DetonateDelay = 0.2;
	
	UFUNCTION()
	void StartDelayedTeleport();
	
	UFUNCTION()
	void HandleTeleportation();
	
public:
	ARLProjectileTeleport();
	
	virtual void BeginPlay() override;
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;
};
