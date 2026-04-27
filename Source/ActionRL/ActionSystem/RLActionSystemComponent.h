// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RLAttributeSet.h"
#include "Components/ActorComponent.h"
#include "RLActionSystemComponent.generated.h"

class URLAttributeSet;
struct FGameplayTag;
class URLAction;

UENUM()
enum class EAttributeModifyType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid,
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayTag /*AttributeTag*/,  float /*NewAttributeValue*/, float /*OldAttributeValue*/ );

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRL_API URLActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	FGameplayTagContainer ActiveGameplayTags;
	
protected:
	
	/** The Attributes set */
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	TObjectPtr<URLAttributeSet> Attributes;
	
	TMap<FGameplayTag, FRLAttribute*> CachedAttributes;
	
	UPROPERTY(EditAnywhere, Category="Attributes")
	TSubclassOf<URLAttributeSet> AttributeSetClass;
	
	TMap<FGameplayTag, FOnAttributeChanged> AttributeListeners;
	
	/* An array to hold all the Actions for the Character */
	UPROPERTY()
	TArray<TObjectPtr<URLAction>> Actions;
	
	/* For Blueprint */
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URLAction>> DefaultActions;
	
public:
	
	URLActionSystemComponent();
	
	/* Initializes the Component on Level Startup */
	virtual void InitializeComponent() override;
	
	/* Applies a change to a ActionSystemComponents Attribute */
	void ApplyAttributeChange(FGameplayTag InAttributeTag, float InValue, EAttributeModifyType ModifyType);
	
	FRLAttribute* GetAttribute(FGameplayTag InAttributeTag);
	
	FOnAttributeChanged& GetAttributeListener(FGameplayTag InAttributeTag);
	
	/** Starts an Actor Action */
	void StartAction(FGameplayTag InActionName);
	
	/** Starts an Actor Action */
	void StopAction(FGameplayTag InActionName);
	
	/** Grants Actions/Abilities to the RLActionSystemComponent as an Array in Actions */
	void GrantAction(TSubclassOf<URLAction> NewActionClass);
	
	void OnHealthChanged(FGameplayTag AttributeTag,  float NewAttributeValue, float OldAttributeValue);
};