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
	AddNativeTag(FName("Attributes.Primary.Strength"), TEXT("Increases physical damage"), GameplayTags.Attributes_Primary_Strength);
	AddNativeTag(FName("Attributes.Primary.Intelligence"), TEXT("Increases magical damage"), GameplayTags.Attributes_Primary_Intelligence);
	AddNativeTag(FName("Attributes.Primary.Resilience"), TEXT("Reduces armor and armor penetration"), GameplayTags.Attributes_Primary_Resilience);
	AddNativeTag(FName("Attributes.Primary.Vigor"), TEXT("Increases Health"), GameplayTags.Attributes_Primary_Vigor);
	
	/* Secondary Attributes */
	AddNativeTag(FName("Attributes.Secondary.Armor"), TEXT("Reduces damage taken, improves block chance"), GameplayTags.Attributes_Secondary_Armor);
	AddNativeTag(FName("Attributes.Secondary.ArmorPenetration"), TEXT("Ignored percentage of enemy armor, increases critical hit chance"), GameplayTags.Attributes_Secondary_ArmorPenetration);
	AddNativeTag(FName("Attributes.Secondary.BlockChance"), TEXT("Chance to cut incoming damage in half"), GameplayTags.Attributes_Secondary_BlockChance);
	AddNativeTag(FName("Attributes.Secondary.CriticalHitChance"), TEXT("Chance to deal critical hit"), GameplayTags.Attributes_Secondary_CriticalHitChance);
	AddNativeTag(FName("Attributes.Secondary.CriticalHitDamage"), TEXT("Increases damage of critical hits"), GameplayTags.Attributes_Secondary_CriticalHitDamage);
	AddNativeTag(FName("Attributes.Secondary.CriticalHitResistance"), TEXT("Reduces chance to receive critical hit"), GameplayTags.Attributes_Secondary_CriticalHitResistance);
	AddNativeTag(FName("Attributes.Secondary.HealthRegeneration"), TEXT("Regenerates health over time"), GameplayTags.Attributes_Secondary_HealthRegeneration);
	AddNativeTag(FName("Attributes.Secondary.ManaRegeneration"), TEXT("Regenerates mana over time"), GameplayTags.Attributes_Secondary_ManaRegeneration);
	AddNativeTag(FName("Attributes.Secondary.MaxHealth"), TEXT("Increases maximum health"), GameplayTags.Attributes_Secondary_MaxHealth);
	AddNativeTag(FName("Attributes.Secondary.MaxMana"), TEXT("Increases maximum mana"), GameplayTags.Attributes_Secondary_MaxMana);
	
	/* Input Tags */
	AddNativeTag(FName("InputTag.LMB"), TEXT("Input tag for Left Mouse Button"), GameplayTags.InputTag_LMB);
	AddNativeTag(FName("InputTag.RMB"), TEXT("Input tag for Right Mouse Button"), GameplayTags.InputTag_RMB);
	AddNativeTag(FName("InputTag.1"), TEXT("Input tag for Keyboard Button 1"), GameplayTags.InputTag_1);
	AddNativeTag(FName("InputTag.2"), TEXT("Input tag for Keyboard Button 2"), GameplayTags.InputTag_2);
	AddNativeTag(FName("InputTag.3"), TEXT("Input tag for Keyboard Button 3"), GameplayTags.InputTag_3);
	AddNativeTag(FName("InputTag.4"), TEXT("Input tag for Keyboard Button 4"), GameplayTags.InputTag_4);
	
	/* Effect Tags */
	AddNativeTag(FName("Damage"), TEXT("Tag for damage effects"), GameplayTags.Damage);
}
