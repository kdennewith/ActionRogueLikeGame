// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLProjectileBase.h"
#include "GameFramework/Actor.h"
#include "RLProjectileBlackhole.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONRL_API ARLProjectileBlackhole : public ARLProjectileBase
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent; /** For the Explosion Force */
	
	UFUNCTION()
	void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFronSweep, const FHitResult& SweepResult);
	
public:
	virtual void PostInitializeComponents() override;
	
	ARLProjectileBlackhole();
	
};
