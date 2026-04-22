// Fill out your copyright notice in the Description page of Project Settings.


#include "RLBTTask_RangedAttack.h"

#include "AIController.h"
#include "RLGameTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Projectiles/RLProjectileBase.h"

URLBTTask_RangedAttack::URLBTTask_RangedAttack()
{
	TargetActorKey.SelectedKeyName = NAME_TargetActor_A;
}

EBTNodeResult::Type URLBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* Pawn = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	check(Pawn);
	FVector SpawnLocation = Pawn->GetMesh()->GetSocketLocation(MuzzleSocketName);
	
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!IsValid(TargetActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetActor is invalid"));
		return EBTNodeResult::Failed;
	}
	
	FVector Direction = TargetActor->GetActorLocation() - SpawnLocation;
	FRotator SpawnRotation = Direction.Rotation();
	
	SpawnRotation.Pitch += FMath::FRandRange(0.f, MaxBulletSpread);
	SpawnRotation.Yaw += FMath::FRandRange(-MaxBulletSpread, MaxBulletSpread);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Pawn;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	
	AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
