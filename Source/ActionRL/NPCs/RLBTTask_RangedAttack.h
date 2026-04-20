// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RLBTTask_RangedAttack.generated.h"

class ARLProjectileBase;
/**
 * 
 */
UCLASS()
class ACTIONRL_API URLBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="AI")
	FName MuzzleSocketName;
	
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<ARLProjectileBase> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="AI")
	float MaxBulletSpread = 5.f;
	
public:
	
	URLBTTask_RangedAttack();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
