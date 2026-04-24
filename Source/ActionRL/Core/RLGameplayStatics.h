// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RLGameplayStatics.generated.h"

class URLActionSystemComponent;
/**
 * 
 */
UCLASS()
class ACTIONRL_API URLGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	static bool IsFullHealth(URLActionSystemComponent* ActionComp);
};
