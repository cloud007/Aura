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
	
protected:
	
private:
	static FAuraGameplayTags GameplayTags;
};
