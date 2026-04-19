// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RLAIController.generated.h"

UCLASS()
class ACTIONRL_API ARLAIController : public AAIController
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	virtual void BeginPlay() override;
	
public:
	
	ARLAIController();
};
