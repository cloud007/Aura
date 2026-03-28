// Copyright - Javackson Studio


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::AddNativeTag(const FName& TagName, const FString& TagComment, FGameplayTag& OutTag)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), TagComment);
}

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	/* Primary Attributes */
	AddNativeTag(FName("Attributes.Primary.Strength"), TEXT("Increases physical damage"), GameplayTags.Atrributes_Primary_Strength);
	AddNativeTag(FName("Attributes.Primary.Intelligence"), TEXT("Increases magical damage"), GameplayTags.Atrributes_Primary_Intelligence);
	AddNativeTag(FName("Attributes.Primary.Resilience"), TEXT("Reduces armor and armor penetration"), GameplayTags.Atrributes_Primary_Resilience);
	AddNativeTag(FName("Attributes.Primary.Vigor"), TEXT("Increases Health"), GameplayTags.Atrributes_Primary_Vigor);
	
	/* Secondary Attributes */
	AddNativeTag(FName("Attributes.Secondary.Armor"), TEXT("Reduces damage taken, improves block chance"), GameplayTags.Atrributes_Secondary_Armor);
	AddNativeTag(FName("Attributes.Secondary.ArmorPenetration"), TEXT("Ignored percentage of enemy armor, increases critical hit chance"), GameplayTags.Atrributes_Secondary_ArmorPenetration);
	AddNativeTag(FName("Attributes.Secondary.BlockChance"), TEXT("Chance to cut incoming damage in half"), GameplayTags.Atrributes_Secondary_BlockChance);
	AddNativeTag(FName("Attributes.Secondary.CriticalHitChance"), TEXT("Chance to deal critical hit"), GameplayTags.Atrributes_Secondary_CriticalHitChance);
	AddNativeTag(FName("Attributes.Secondary.CriticalHitDamage"), TEXT("Increases damage of critical hits"), GameplayTags.Atrributes_Secondary_CriticalHitDamage);
	AddNativeTag(FName("Attributes.Secondary.CriticalHitResistance"), TEXT("Reduces chance to receive critical hit"), GameplayTags.Atrributes_Secondary_CriticalHitResistance);
	AddNativeTag(FName("Attributes.Secondary.HealthRegeneration"), TEXT("Regenerates health over time"), GameplayTags.Atrributes_Secondary_HealthRegeneration);
	AddNativeTag(FName("Attributes.Secondary.ManaRegeneration"), TEXT("Regenerates mana over time"), GameplayTags.Atrributes_Secondary_ManaRegeneration);
	AddNativeTag(FName("Attributes.Secondary.MaxHealth"), TEXT("Increases maximum health"), GameplayTags.Atrributes_Secondary_MaxHealth);
	AddNativeTag(FName("Attributes.Secondary.MaxMana"), TEXT("Increases maximum mana"), GameplayTags.Atrributes_Secondary_MaxMana);
}
