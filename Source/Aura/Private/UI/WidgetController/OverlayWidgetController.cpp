// Copyright - Javackson Studio


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAS->GetHealth(), AuraAS->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAS->GetMana(), AuraAS->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAS->GetHealthAttribute()).AddLambda([this, AuraAS](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue, AuraAS->GetMaxHealth());
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAS->GetMaxHealthAttribute()).AddLambda([this, AuraAS](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(AuraAS->GetHealth(), Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAS->GetManaAttribute()).AddLambda([this, AuraAS](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(AuraAS->GetMana(), Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAS->GetMaxManaAttribute()).AddLambda([this, AuraAS](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue, AuraAS->GetMaxMana());
	});
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			if (!Tag.IsValid() || !MessageWidgetDataTable)
			{
				continue;	
			}
			const FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (MessageTag.IsValid() && Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow* DataTableRowByTag = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				if (DataTableRowByTag)
				{
					MessageWidgetRowDelegate.Broadcast(*DataTableRowByTag);
				}
			}
		}
	});
}
