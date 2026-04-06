// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RLPlayerController.generated.h"

class URLInteractionComponent;
class UInputAction;
/**
 * 
 */
UCLASS()
class ACTIONRL_API ARLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category=Components)
	TObjectPtr<URLInteractionComponent> InteractionComponent;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> Input_Interact;
	
	void StartInteract();
	
	virtual void SetupInputComponent() override; 
	
public:
	
	ARLPlayerController();
};
