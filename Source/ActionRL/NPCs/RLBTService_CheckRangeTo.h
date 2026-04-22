// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BTService.h"
#include "RLBTService_CheckRangeTo.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRL_API URLBTService_CheckRangeTo : public UBTService
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector WithinRangeKey;
	
	UPROPERTY(EditAnywhere, Category="AI")
	float MaxAttackRange = 650.f;
	
public:
	
	URLBTService_CheckRangeTo();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime) override;
};
