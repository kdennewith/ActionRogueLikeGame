// Fill out your copyright notice in the Description page of Project Settings.


#include "RLPlayerCharacter.h"
#include "Projectiles/RLProjectileMagic.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "RLGameTypes.h"
#include "ActionSystem/RLActionSystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

/* Constructor Defaults Values */
ARLPlayerCharacter::ARLPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ActionSystemComponent = CreateDefaultSubobject<URLActionSystemComponent>(TEXT("ActionSystemComp"));
	
	//! SpringArm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent); //! Attached to the Root Component
	SpringArmComponent->bUsePawnControlRotation = true; /** bUse is a BluePrint control which is kinda cool */
	
	//! Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp")); //! Use TEXT for good good.
	CameraComponent->SetupAttachment(SpringArmComponent); //! Attached to the Root Component
	
	MuzzleSocketName = "Muzzle_01"; /* Used for the Projectile Hand */
}

void ARLPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &ARLPlayerCharacter::OnHealthChanged);
}

// Called to bind functionality to input
void ARLPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Standard Input Mapping UE5 */
	auto EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	/* The Move Binding */
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARLPlayerCharacter::Move);
	
	/* The Look Binding */
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARLPlayerCharacter::Look);
	
	/** The Jump Binding */
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ARLPlayerCharacter::Jump);
	
	/* The Primary Attack Binding */
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, 
		&ARLPlayerCharacter::StartAction, FName("PrimaryAttack"));
	
	/* The Secondary Attack Binding */
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, 
		&ARLPlayerCharacter::StartProjectileAttack, SecondaryAttackProjectileClass);
	
	/* The Special Attack Binding */
	EnhancedInput->BindAction(Input_SpecialAttack, ETriggerEvent::Triggered, this, 
		&ARLPlayerCharacter::StartProjectileAttack, SpecialAttackProjectileClass);
	
}

void ARLPlayerCharacter::Move(const FInputActionValue& InValue)
{
	/* Get's the input value for the Movement keys and stores it in a 2D vector */
	FVector2D InputValue = InValue.Get<FVector2D>();
	
	/* Gets the current controller rotation Rotator Object, used for movement. */
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	
	/* Forward & Back */
	AddMovementInput(ControlRot.Vector(), InputValue.X); /** This means it's going to move in the direction where Character Direction is going (1 Forward, -1 Backward) */
	
	/* Left & Right */
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector); /** This is for the Sideways movement inputs. (Right 1, Left -1) */
	AddMovementInput(RightDirection, InputValue.Y);
}

/** This function used for Looking around using X and Y Coordinates of the Input Value to control the Pitch and Yaw of
 *  the PlayerControllerRotation through AddControllerPitchInput & AddControllerYawInput.	*/																				  
void ARLPlayerCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
	
}

/** This function plays an Attack Animation using a UAnimMontage that is set in BluePrint through the AttackMontage 
 *  variable in the 'PrimaryAttack' Category.
 */
void ARLPlayerCharacter::StartProjectileAttack(TSubclassOf<ARLProjectileBase> ProjectileClass)
{
	/* Plays the Animation Montage 'AttackMontage'<UAnimMontage> to simulate an Attack Animation */
	PlayAnimMontage(AttackMontage);
	
	/* Input Params: SystemTemplate, AttachToComponent, AttachPoint, Location, Rotation, LocationType, AutoDestroy. 
	 * Used to attach the CastingEffect to a Socket on a Mesh, in this case the RLPlayerCharacters Mesh. This will Auto
	 * Destroy itself and uses Zero Vectors for Location and Rotation to not compromise the Muzzle Location.
	 */
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	/* Plays the Casting Sound locally */
	UGameplayStatics::PlaySound2D(this, CastingSound); /* Not for Multiplayer */
	
	/* Using a Delegate to get the timer for the Projectile */
	FTimerDelegate Delegate;
	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	
	Delegate.BindUObject(this, &ARLPlayerCharacter::AttackTimerElapsed, ProjectileClass);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, Delegate, AttackDelayTime, false);
	
}

void ARLPlayerCharacter::AttackTimerElapsed(TSubclassOf<ARLProjectileBase> ProjectileClass)
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName); /* Spawns from the hand of the Actor called MuzzleSocket1 on the Blueprint */
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this; /* Used for Damage Handling */
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	FVector EyeLocation = CameraComponent->GetComponentLocation();
	FRotator EyeRotation = GetControlRotation();
	
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 5000.f); /* Vector directly in front of the Characters Eyes, or the Camera */ 
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	
	UWorld* World = GetWorld(); /* Getting the World Pointer to not call GetWorld() over and over Below */
	
	FVector AdjustTargetLocation;
	FHitResult Hit;
	if (World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_PROJECTILE, CollisionParams))
	{
		AdjustTargetLocation = Hit.Location;
	}
	else
	{
		AdjustTargetLocation = TraceEnd;
	}
	
	FRotator SpawnRotation = (AdjustTargetLocation - SpawnLocation).Rotation();
	
	AActor* NewProjectile = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams); /* Spawns something */
	
	MoveIgnoreActorAdd(NewProjectile); /* So the Projectile goes through your own character. */
	
	float DebugDrawDuration = 5.f;
	
	
	/* The Hit Location or Trace end */
	//DrawDebugBox(World, AdjustTargetLocation, FVector(20.f), FColor::Green, false, DebugDrawDuration);
	
	/* Adjustment Line Trace */
	//DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Green, false, DebugDrawDuration);
	
	/* New Projectile Path */
	//DrawDebugLine(World, SpawnLocation, AdjustTargetLocation, FColor::Yellow, false, DebugDrawDuration);
	
	/* The original Path of the Projectile */
	//DrawDebugLine(World, SpawnLocation, SpawnLocation + (GetControlRotation().Vector() * 5000.f), FColor::Purple,
	//	false, DebugDrawDuration);
}

void ARLPlayerCharacter::StartAction(FName InActionName)
{
	ActionSystemComponent->StartAction(InActionName);
}

void ARLPlayerCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	/* Dun Goofed and Died? */
	if (FMath::IsNearlyZero(NewHealth))
	{
		/* Disables the input on the Player and not the Controller so you can use a Menu when you die */
		DisableInput(nullptr);
		
		/* Stop the movement of the Pawn */
		GetMovementComponent()->StopMovementImmediately();
		
		/* Plays the Death Animation */
		PlayAnimMontage(DeathMontage);
	}
}

float ARLPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                     class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	/* Apply the Health Change Stuff here */
	ActionSystemComponent->ApplyDamage(-DamageAmount);
	
	return ActualDamage;
}

