// Fill out your copyright notice in the Description page of Project Settings.

#include "RLAction_ProjectileAttack.h"
#include "RLActionSystemComponent.h"
#include "RLGameTypes.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Projectiles/RLProjectileBase.h"

URLAction_ProjectileAttack::URLAction_ProjectileAttack()
{
	MuzzleSocketName = "Muzzle_01";
	
	CooldownTime = 0.5f;
}

void URLAction_ProjectileAttack::StartAction_Implementation()
{
	Super::StartAction_Implementation();
	
	/* Getting the Parent Component */
	URLActionSystemComponent* ActionComp = GetOwningComponent();
	
	/* A Character, which is the Parent of the RLActionSystemComponent for usage with GetMesh and AnimMontage.
	 * Will fail if the Cast doesn't work. */
	ACharacter* Character = CastChecked<ACharacter>(ActionComp->GetOwner());
	
	/* Plays the Animation Montage 'AttackMontage'<UAnimMontage> to simulate an Attack Animation */
	Character->PlayAnimMontage(AttackMontage);
	
	/* Input Params: SystemTemplate, AttachToComponent, AttachPoint, Location, Rotation, LocationType, AutoDestroy. 
	 * Used to attach the CastingEffect to a Socket on a Mesh, in this case the RLPlayerCharacters Mesh. This will Auto
	 * Destroy itself and uses Zero Vectors for Location and Rotation to not compromise the Muzzle Location.
	 */
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, Character->GetMesh(), MuzzleSocketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	/* Plays the Casting Sound locally */
	UGameplayStatics::PlaySound2D(this, CastingSound); /* Not for Multiplayer */
	
	/* Using a Delegate to get the timer for the Projectile */
	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ThisClass::AttackTimerElapsed, AttackDelayTime, false);
	StopAction();
}

void URLAction_ProjectileAttack::AttackTimerElapsed()
{
	/* Getting the Parent Component */
	URLActionSystemComponent* ActionComp = GetOwningComponent();
	
	/* A Character, which is the Parent of the RLActionSystemComponent for usage with GetMesh and AnimMontage.
	 * Will fail if the Cast doesn't work. */
	ACharacter* Character = CastChecked<ACharacter>(ActionComp->GetOwner());
	
	/* Spawns from the hand of the Actor called MuzzleSocket1 on the Blueprint */
	FVector SpawnLocation = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
	
	/* Used for Damage Handling */
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Character;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	/* Camera Location Parameters and Setting */
	FVector EyeLocation;
	FRotator EyeRotation;
	Character->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);
	
	/* Ignoring the Character for Collisions with the Projectile */
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Character);
	
	/* Getting the World Pointer to not call GetWorld() over and over Below */
	FVector AdjustTargetLocation;
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 5000.f);
	FHitResult Hit;
	UWorld* World = GetWorld();
	if (World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_PROJECTILE, CollisionParams))
	{
		AdjustTargetLocation = Hit.Location;
	}
	else
	{
		AdjustTargetLocation = TraceEnd;
	}
	
	FRotator SpawnRotation = (AdjustTargetLocation - SpawnLocation).Rotation();
	
	/* Spawns the New Projectile */
	AActor* NewProjectile = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	/* So the Projectile goes through your own character. */
	Character->MoveIgnoreActorAdd(NewProjectile);
	
	StopAction();
}
