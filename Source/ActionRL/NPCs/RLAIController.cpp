// Fill out your copyright notice in the Description page of Project Settings.


#include "RLAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


ARLAIController::ARLAIController()
{
	
}

void ARLAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviorTree);
	
	FName TargetActor = FName("TargetActor");
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0); /* Not compatible with Multiplayer */
	check(PlayerPawn);
	/* Placeholder Code */
	GetBlackboardComponent()->SetValueAsObject(TargetActor, PlayerPawn);
}


