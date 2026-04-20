// Fill out your copyright notice in the Description page of Project Settings.


#include "RLEnvQueryContext_TargetActor.h"

#include "AIController.h"
#include "RLGameTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void URLEnvQueryContext_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	/* Expected Character */ 
	APawn* QuerierPawn = Cast<APawn>(QueryInstance.Owner.Get());
	
	if (ensure(QuerierPawn))
	{
		AAIController* Controller = Cast<AAIController>(QuerierPawn->GetController());
		check(Controller);
		
		AActor* TargetActor = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(NAME_TargetActor));
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);	
	}
}
