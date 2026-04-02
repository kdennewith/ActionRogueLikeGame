// Fill out your copyright notice in the Description page of Project Settings.


#include "RLCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values
ARLCharacter::ARLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//! SpringArm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent); //! Attached to the Root Component
	
	//! Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp")); //! Use TEXT for good good.
	CameraComponent->SetupAttachment(SpringArmComponent); //! Attached to the Root Component
	
}

// Called when the game starts or when spawned
void ARLCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARLCharacter::Move(const FInputActionValue& InValue)
{
	FVector2d InputValue = InValue.Get<FVector2D>();
	
	FVector MoveDirection = FVector(InputValue.X, InputValue.Y, 0.0f);
	
	AddMovementInput(MoveDirection);
}

// Called every frame
void ARLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent); /** Standard Input Mapping UE5 */
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARLCharacter::Move);
}

