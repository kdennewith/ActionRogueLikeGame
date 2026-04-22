// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RLBTDecorator_IsLowHealth.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRL_API URLBTDecorator_IsLowHealth : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	
	
	UPROPERTY(EditAnywhere, Category="AI", meta=(ClampMin="0.0", ClampMax="1.0")) /* Clamped between 0-100% */
	float LowHealthThreshold = 0.3f;
	
public:
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
