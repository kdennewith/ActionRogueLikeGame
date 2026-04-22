// Fill out your copyright notice in the Description page of Project Settings.


#include "RLBTTask_FleeHeal.h"

#include "AIController.h"
#include "ActionSystem/RLActionSystemComponent.h"

EBTNodeResult::Type URLBTTask_FleeHeal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	check(Pawn);
	
	URLActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URLActionSystemComponent>();
	if (ensure(ActionComp))
	{
		ActionComp->ApplyHealing(HealAmount);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
