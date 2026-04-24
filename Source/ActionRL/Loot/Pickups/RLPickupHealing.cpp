// Fill out your copyright notice in the Description page of Project Settings.


#include "RLPickupHealing.h"

#include "RLGameplayTags.h"
#include "ActionSystem/RLActionSystemComponent.h"
#include "Core/RLGameplayStatics.h"
#include "Kismet/GameplayStatics.h"

ARLPickupHealing::ARLPickupHealing()
{

}

void ARLPickupHealing::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFronSweep, const FHitResult& SweepResult)
{
	URLActionSystemComponent* ActionComp = OtherActor->GetComponentByClass<URLActionSystemComponent>();
	
	if (ensure(ActionComp != nullptr) && !URLGameplayStatics::IsFullHealth(ActionComp))
	{
		ActionComp->ApplyAttributeChange(RLGameplayTags::Attribute_Health ,HealingAmount, EAttributeModifyType::Base);
		
		UGameplayStatics::PlaySoundAtLocation(this, PickupSoundComponent, GetActorLocation(), FRotator::ZeroRotator);
		
		Destroy();
	}
	
}




