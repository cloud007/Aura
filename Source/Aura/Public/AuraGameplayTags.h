// Copyright - Javackson Studio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 * 
 * Singleton containing native gameplay tags for the Aura project. 
 * 
 * This class is used to avoid hardcoding gameplay tags throughout the codebase and to provide a single source of truth for all gameplay tags used in the project.
 * 
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
	FGameplayTag Atrributes_Primary_Strength;
	FGameplayTag Atrributes_Primary_Intelligence;
	FGameplayTag Atrributes_Primary_Resilience;
	FGameplayTag Atrributes_Primary_Vigor;
	
	FGameplayTag Atrributes_Secondary_Armor;
	FGameplayTag Atrributes_Secondary_ArmorPenetration;
	FGameplayTag Atrributes_Secondary_BlockChance;
	FGameplayTag Atrributes_Secondary_CriticalHitChance;
	FGameplayTag Atrributes_Secondary_CriticalHitDamage;
	FGameplayTag Atrributes_Secondary_CriticalHitResistance;
	FGameplayTag Atrributes_Secondary_HealthRegeneration;
	FGameplayTag Atrributes_Secondary_ManaRegeneration;
	FGameplayTag Atrributes_Secondary_MaxHealth;
	FGameplayTag Atrributes_Secondary_MaxMana;
	
protected:
	
private:
	static FAuraGameplayTags GameplayTags;
	static void AddNativeTag(const FName& TagName, const FString& TagComment, FGameplayTag& OutTag);
};
