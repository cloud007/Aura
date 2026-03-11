// Copyright - Javackson Studio


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BrodcastInitialValues()
{
	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAS->GetHealth(), AuraAS->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAS->GetMana(), AuraAS->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAS->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAS->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAS->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAS->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	
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

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(Data.NewValue, AuraAS->GetMaxHealth());
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAS->GetHealth(), Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnManaChanged.Broadcast(Data.NewValue, AuraAS->GetMaxMana());
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnManaChanged.Broadcast(AuraAS->GetMana(), Data.NewValue);
}
