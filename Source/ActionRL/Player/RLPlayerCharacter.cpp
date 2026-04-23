// Fill out your copyright notice in the Description page of Project Settings.


#include "RLPlayerCharacter.h"
#include "ActionSystem/RLActionSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

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
}

void ARLPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
}

// Called to bind functionality to input
void ARLPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Standard Input Mapping UE5 */
	auto EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	/* The Move Binding */
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	
	/* The Look Binding */
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ThisClass::Look);
	
	/** The Jump Binding */
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ThisClass::Jump);
	
	/* The Sprint Start Binding */
	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Started, this, 
		&ThisClass::StartAction, FName("Sprint"));
	
	/* The Sprint Complete Binding */
	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Completed, this, 
		&ThisClass::StopAction, FName("Sprint"));
	
	/* The Primary Attack Binding */
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, 
		&ThisClass::StartAction, FName("PrimaryAttack"));
	
	/* The Secondary Attack Binding */
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, 
		&ThisClass::StartAction, FName("SecondaryAttack"));
	
	/* The Special Attack Binding */
	EnhancedInput->BindAction(Input_SpecialAttack, ETriggerEvent::Triggered, this, 
		&ThisClass::StartAction, FName("SpecialAttack"));
	
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

/** Starts an Action for the RLPlayerCharacter */
void ARLPlayerCharacter::StartAction(FName InActionName)
{
	ActionSystemComponent->StartAction(InActionName);
}

void ARLPlayerCharacter::StopAction(FName InActionName)
{
	ActionSystemComponent->StopAction(InActionName);
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

