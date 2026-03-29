// Copyright - Javackson Studio


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	for (const FAuraAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		if (const auto* FuncPtr = AuraAttributeSet->TagsToAttributes.Find(Info.AttributeTag))
		{
			const FGameplayAttribute Attribute = (*FuncPtr)();
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda([this, Info, Attribute](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Attribute, Info);
			});
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find Attribute for Tag [%s] on AttributeMenuWidgetController [%s]"), *Info.AttributeTag.ToString(), *GetNameSafe(this));
		}
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayAttribute& Attribute, const FAuraAttributeInfo& Info) const
{
	FAuraAttributeInfo InfoWithValue = Info;
	InfoWithValue.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(InfoWithValue);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	check(AttributeInfo);

	for (const FAuraAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		if (const auto* FuncPtr = AuraAttributeSet->TagsToAttributes.Find(Info.AttributeTag))
		{
			BroadcastAttributeInfo((*FuncPtr)(), Info);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Can't find Attribute for Tag [%s] on AttributeMenuWidgetController [%s]"), *Info.AttributeTag.ToString(), *GetNameSafe(this));
		}
	}
}
