// Fill out your copyright notice in the Description page of Project Settings.


#include "RLPlayerController.h"

#include "EnhancedInputComponent.h"
#include "RLInteractionComponent.h"

ARLPlayerController::ARLPlayerController()
{
	InteractionComponent = CreateDefaultSubobject<URLInteractionComponent>(TEXT("InteractionComp"));
}

void ARLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	auto EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent); /** Standard Input Mapping UE5 */
	
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ARLPlayerController::StartInteract);
}

void ARLPlayerController::StartInteract()
{
	InteractionComponent->Interact();
}
