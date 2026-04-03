// Copyright - Javackson Studio

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Actor/AuraProjectile.h"
#include "AuraProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category="Projectile")
	bool SpawnProjectile();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
