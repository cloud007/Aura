// Copyright - Javackson Studio


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& StartupAbility : StartupAbilities)
	{
		if (IsValid(StartupAbility))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbility, 1);
			GiveAbilityAndActivateOnce(AbilitySpec);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid Ability in Startup Abilities on AuraAbilitySystemComponent"));
		}
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, 
                                                FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTags.Broadcast(TagContainer);
}
