// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RLPlayerCharacter.generated.h"

class ARLProjectileMagic;
struct FInputActionInstance;
struct FInputActionValue;
class UAnimMontage;
class UCameraComponent;
class UInputAction;
class UNiagaraSystem;
class USpringArmComponent;

UCLASS()
class ACTIONRL_API ARLPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARLPlayerCharacter();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<ARLProjectileMagic> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(VisibleAnywhere, Category="PrimaryAttack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent; //! The Camera
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent; //! The SpringArm
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& InValue);
	
	void Look(const FInputActionInstance& InValue);
	
	void PrimaryAttack();

	void AttackTimerElapsed();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
