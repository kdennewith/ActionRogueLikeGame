// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLItemChest.generated.h"

UCLASS()
class ACTIONRL_API ARLItemChest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARLItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
