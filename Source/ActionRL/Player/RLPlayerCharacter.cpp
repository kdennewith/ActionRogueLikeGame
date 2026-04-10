// Fill out your copyright notice in the Description page of Project Settings.


#include "RLPlayerCharacter.h"
#include "Projectiles/RLProjectileMagic.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

/* Constructor Defaults Values */
ARLPlayerCharacter::ARLPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//! SpringArm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent); //! Attached to the Root Component
	SpringArmComponent->bUsePawnControlRotation = true; /** bUse is a BluePrint control which is kinda cool */
	
	//! Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp")); //! Use TEXT for good good.
	CameraComponent->SetupAttachment(SpringArmComponent); //! Attached to the Root Component
	
	MuzzleSocketName = "Muzzle_01"; /* Used for the Projectile Hand */
}

// Called when the game starts or when spawned
void ARLPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ARLPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent); /** Standard Input Mapping UE5 */
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARLPlayerCharacter::Move); /* The Move Binding */
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARLPlayerCharacter::Look); /* The Look Binding */
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ARLPlayerCharacter::Jump); /** The Jump Binding */
	
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, 
		&ARLPlayerCharacter::StartProjectileAttack, PrimaryAttackProjectileClass); /* The Primary Attack Binding */
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, 
		&ARLPlayerCharacter::StartProjectileAttack, SecondaryAttackProjectileClass); /* The Secondary Attack Binding */
	EnhancedInput->BindAction(Input_SpecialAttack, ETriggerEvent::Triggered, this, 
		&ARLPlayerCharacter::StartProjectileAttack, SpecialAttackProjectileClass); /* The Special Attack Binding */
	
}

void ARLPlayerCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>(); /* Get's the input value for the Movement keys and stores it in a 2D vector */
	
	FRotator ControlRot = GetControlRotation(); /* Gets the current controller rotation Rotator Object, used for movement. */
	ControlRot.Pitch = 0.0f;
	
	//! Forward & Back
	AddMovementInput(ControlRot.Vector(), InputValue.X); /** This means it's going to move in the direction where Character Direction is going (1 Forward, -1 Backward) */
	
	//! Left & Right
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector); /** This is for the Sideways movement inputs. (Right 1, Left -1) */
	AddMovementInput(RightDirection, InputValue.Y);
}

/** Look Function */
void ARLPlayerCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

/** Start Projectile Attack Function */
void ARLPlayerCharacter::StartProjectileAttack(TSubclassOf<ARLProjectileBase> ProjectileClass)
{
	
	PlayAnimMontage(AttackMontage);
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	UGameplayStatics::PlaySound2D(this, CastingSound); /* Not for Multiplayer */
	
	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	
	/* Using a Delegate to get the timer for the Projectile */
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ARLPlayerCharacter::AttackTimerElapsed, ProjectileClass);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, Delegate, AttackDelayTime, false);
	
}

void ARLPlayerCharacter::AttackTimerElapsed(TSubclassOf<ARLProjectileBase> ProjectileClass)
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this; /* Used for Damage Handling */
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams); /* Spawns something */
	
	MoveIgnoreActorAdd(NewProjectile); /* So the Projectile goes through your own character. */
}


void ARLPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

