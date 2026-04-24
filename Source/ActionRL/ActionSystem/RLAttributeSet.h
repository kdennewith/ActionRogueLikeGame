// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RLAttributeSet.generated.h"


USTRUCT()
struct FRLAttribute
{
	GENERATED_BODY()
	
	FRLAttribute() {}
	
	FRLAttribute(float InBase) : Base(InBase) {}
	
	UPROPERTY(EditAnywhere)
	float Base = 0.f;
	
	UPROPERTY(Transient)
	float Modifier = 0.f;
	
	float GetValue() const {return Base + Modifier;}
};


/**
 * Base ----------------------------------------------------------------------------------------------------------------
 */
UCLASS()
class ACTIONRL_API URLAttributeSet : public UObject
{
	GENERATED_BODY()
	
public:
	
	virtual void PostAttributeChanged() {};
};

/**
 * Health Attribute Set ------------------------------------------------------------------------------------------------
 */
UCLASS()
class URLHealthAttributeSet : public URLAttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category="Attributes")
	FRLAttribute Health;
	
	UPROPERTY(EditAnywhere, Category="Attributes")
	FRLAttribute HealthMax;
	
	virtual void PostAttributeChanged() override;
	
	URLHealthAttributeSet();
};
