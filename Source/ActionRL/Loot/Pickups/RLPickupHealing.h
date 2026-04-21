// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLPickupBase.h"
#include "GameFramework/Actor.h"
#include "RLPickupHealing.generated.h"

UCLASS()
class ACTIONRL_API ARLPickupHealing : public ARLPickupBase
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, Category="Healing")
	float HealingAmount = 50.0f;
	
	virtual void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFronSweep, const FHitResult& SweepResult) override;
	
public:
	
	ARLPickupHealing();

};
